#include <cstring>
#include <fstream>
#include <thread>
#include "ExternalFunctions.h"
#include "costanti.hpp"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "bonus.h"
#include "Enemy.h"
using namespace std;

/*  Author:         Alice Benatti
    Parameters:     filename -> il nome del file dove e' salvata la classifica
    Return value:   void
    Comments:       Costruttore della classe Scoreboard
*/
Scoreboard::Scoreboard(char filename[]){
    strcpy(this->filename, filename);
    this->head = this->get_file();
}

/*  Author:         Alice Benatti
    Parameters:     void
    Return value:   Lista contenente nomi e punteggi dei player in scoreboard.
    Comments:       Leggo le stringhe del file finchè non giungo alla fine dello stesso.
*/
ptr_scoreboard_list Scoreboard::get_file(void){
    ifstream open_file;
    open_file.open(this->filename,ios::in);
    int c;
    ptr_scoreboard_list head = NULL;
    ptr_scoreboard_list aux = NULL;
    ptr_scoreboard_list tmp = NULL;
    int pass;
    string my_string;
    int count = 1;  
    while (!is_file_empty(open_file) &&!open_file.eof() && count < 10){
        tmp = new scoreboard_list;
        getline(open_file, my_string, '\n');
        if(strcmp(my_string.c_str(), "")){
            strcpy(tmp->nick, my_string.substr(my_string.find(' ',1)+1, my_string.find(' ', 3)-2).c_str());   
            tmp->score = stoi(my_string.substr(my_string.find(' ', 2)+1, my_string.find('\n')-1));
            if (head == NULL){
                head = new scoreboard_list;
                head = tmp;
                aux = tmp;
                tmp = NULL;
            }else{
                aux->next = tmp;
                aux = aux->next;
                tmp = NULL;
            }
            count ++;
        }
    }
    aux->next = NULL;
    open_file.close();
    this->head = head;
    return head;
}

/*  Author:         Alice Benatti
    Parameters:     score -> punteggio fatto dal player.
                    nick -> nome del player.
    Return value:   void
    Comments:       Cerco nella lista il punto esatto in cui inserire il punteggio.
                    L'obiettivo è ovviamente quello di mantenere una lista ordinata decrescentemente.
*/
void Scoreboard::add_value(int score, char nick[]){
    ptr_scoreboard_list tmp = this->head;
    ptr_scoreboard_list new_val = new scoreboard_list;
    new_val->score = score;
    strcpy(new_val->nick, nick);
    if (tmp == NULL){
        new_val->next = NULL;
        this->head = new_val;
    }else if (tmp->score < new_val->score ){
        this->head = new_val;
        new_val->next = tmp;
    }else{
        bool exit = false;
        while (tmp->next != NULL && exit == false){
            if (tmp->next->score <= new_val->score){
                new_val->next = tmp->next;
                tmp->next = new_val;
                exit = true;
            }
            tmp = tmp->next;
        }
        if (exit == false){
            tmp->next = new_val;
            new_val->next = NULL;
        }
    }
}

/*  Author:         Alice Benatti
    Parameters:     void
    Return value:   void
    Comments:       salvo nel file Leaderboard.txt la lista appena aggiornata.
*/
void Scoreboard::save_file(){
    ptr_scoreboard_list tmp = this->head;
    ofstream myfile;
    myfile.open(this->filename);
    int i = 1;
    while (tmp != NULL){         
        myfile<<i<<" "<<tmp->nick<<" "<<tmp->score;
        if(tmp->next != NULL){
            myfile<<"\n";
        }
        myfile.flush();
        tmp = tmp->next;
        i++;
    }
    myfile.close();
}

/*  Author:         Alice Benatti
    Parameters:     position -> posizione in classifica di un elemento.
    Return value:   Puntatore all'elemento cercato nella lista in cui sono salvati gli elementi in classifica.
    Comments:       Scorro la lista di 'position' ottenendo l'elemento da me cercato. 
*/
ptr_scoreboard_list Scoreboard::get_position(int position){
    ptr_scoreboard_list tmp = this->head;
    int i = 1;
    while(i < position && tmp != NULL){
        tmp = tmp->next;
        i++;
    }
    if(i != position){
        return NULL;
    }
    return tmp;
}
 