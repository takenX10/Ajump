#include <cstring>
#include <fstream>
#include <thread>
#include "ExternalFunctions.h"
#include "costanti.hpp"
#include "Gioco.h"
#include "Mappa.h"
#include "Player.h"
#include "bonus.h"
#include "Nemici.h"
using namespace std;

Classifica::Classifica(char filename[]){
    strcpy(this->filename, filename);
    this->head = this->get_file();
}

/*
    Author: Alice Benatti
    Parameters: void
    Return value: Lista contenente nomi e punteggi dei player in scoreboard.
    Comments: Leggo le stringhe del file finchè non giungo alla fine dello stesso.
*/

plista Classifica::get_file(void){
    ifstream OpenFile;
    OpenFile.open(this->filename,ios::in);
    int c;
    plista head = NULL;
    plista aux = NULL;
    plista tmp = NULL;
    int pass;
    string stringa; // TODO: rimuovi questo
    int count = 1;  
    while (!is_file_empty(OpenFile) &&!OpenFile.eof() && count < 10){
        tmp = new lista_classifica;
        getline(OpenFile, stringa, '\n');
        if(strcmp(stringa.c_str(), "")){
            strcpy(tmp->nick, stringa.substr(stringa.find(' ',1)+1, stringa.find(' ', 3)-2).c_str());   
            tmp->score = stoi(stringa.substr(stringa.find(' ', 2)+1, stringa.find('\n')-1));

            if (head == NULL){
                head = new lista_classifica;
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
    OpenFile.close();
    this->head = head;
    return head;
}



/*
    Author: Alice Benatti
    Parameters: score -> punteggio fatto dal player.
                nick -> nome del player.
    Return value: void
    Comments: Cerco nella lista il punto esatto in cui inserire il punteggio.
              L'obiettivo è ovviamente quello di mantenere una lista ordinata decrescentemente.
*/

void Classifica::add_value(int score, char nick[]){
    plista tmp = this->head;
    plista new_val = new lista_classifica;
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


/*
    Author: Alice Benatti
    Parameters: void
    Return value: void
    Comments: salvo nel file Leaderboard.txt la lista appena aggiornata.
*/


void Classifica::save_file(){
    plista tmp = this->head;
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


/*
    Author: Alice Benatti
    Parameters: position -> posizione in classifica di un elemento.
    Return value: Puntatore all'elemento cercato nella lista in cui sono salvati gli elementi in classifica.
    Comments: Scorro la lista di 'position' ottenendo l'elemento da me cercato. 
*/
plista Classifica::get_position(int position){
    plista tmp = this->head;
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



/*
    Author: Alice Benatti
    Parameters: LBoard -> Scoreboard
    Return value: void
    Comments: Schermata iniziale del gioco. Permette la visualizzazione della classifica e di iniziare la partita.
*/

void StartScreen(Classifica LBoard){
    clearscreen();
    char key; bool check= false;
    color(Black, Light_Yellow);
    printfile("Documents\\name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER to play" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "              >> press ESC to exit" << endl;
    color(Black, Light_Green);
    do{
        key=getch();
        if (key==ENTER){
            check = true;
            PrintMap(LBoard);
        } 
        else if (key== 'C' || key=='c') {
            check= true;
            Leaderboard(LBoard);
        }
        else if (key==ESC){ check = true; clearscreen(); exit(0); }
        else cout << "\nERROR: INSERT A CORRECT VALUE" << endl;
    }
    while (check==false);
}


/*
    Author: Alice Benatti(?)
    Parameters: LBoard -> Scoreboard 
    Return value: void
    Comments: La funzione permette l'avvio del gioco.
*/

//TODO: si potrebbe fare un file a parte per questa printmap(?) Essendo praticamente il vero main del gioco.
//TODO: ma passare il parametro LBoard è necessario(?) Non saprei come spiegarne il senso.


void PrintMap(Classifica LBoard){
    clearscreen();
    color(Black, White);
    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    BulletList proiettili = BulletList(&m, &p);
    Lista_nemici ent = Lista_nemici(&m, &p, &proiettili);
    Bonus bonus = Bonus(&m, &p, &ent, &proiettili);
    Gioco  g = Gioco(&m, &p, &proiettili, &ent, &bonus);

    hide_cursor(); // Rende il cursore invisibile

    thread print_map_thread(&Gioco::auto_print_map, g);
    thread get_position(&Gioco::keyListener, g);

    print_map_thread.join();
    GameOver((m.getTotalHeight()-29)/2);
}


/*
    Author: Alice Benatti
    Parameters: score -> punteggio ottenuto dal player che ha appena terminato la partita.
    Return value: void
    Comments: La funzione viene chiamata al termine della partita. 
              Permette di salvare il punteggio nella leaderboard, aggiornarla, e visualizzarla.
              L'utente può anche scegliere di non salvare il punteggio, uscendo così dal gioco.
*/


void GameOver(int score){
    clearscreen();
    char key;
    char input[CHAR_VALUE];
    int id;
    bool check = false;
    int socreboard_lenght;
    Classifica LBoard = Classifica("Documents\\leaderboard.txt");
    color(Red, Bright_White);
    char stringa[15];
    strcpy(stringa, "Documents\\gameover.txt");
    printfile(stringa);
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        do{
            cin>>key;
            if ((int)key == 'y' || (int)key == 'Y') {
                check = true;
                cout << "Insert ur nick: ";
                cin >> input;
                //apro il file e salvo i valori vecchi
                LBoard.get_file();
                LBoard.add_value(score, input);
                LBoard.save_file();
                cout << "Ur score has been saved"<< endl;
            }
            else if ((int)key == 'n' || (int)key == 'N') {
                check = true;
                cout << "\n\n       >> Okay! Press SPACE to exit the game" << endl;
                do{
                    key=getch();
                    if ((int)key == SPACE) exit(0);
                    
                    else cout << "ERROR: INSERT A CORRECT VALUE" << endl;  
                } while(true);
            }
            else{
                check = false;
                cout << "ERROR: INSERT A CORRECT VALUE" << endl; 
            }

        }while (check==false);
        printTop(LBoard);
        cout << "\n\n       >> press SPACE to exit the game "<< endl;
        do{
            key=getch();
            if ((int)key == SPACE) exit(0);
            else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
        } while(true);
    } while(true);
}



/*
    Author: Alice Benatti
    Parameters: classifica -> lista contenente la classifica.
    Return value: void
    Comments: Pulisce lo schermo e chiama una funzione che stamperà la classifica.
*/

void Leaderboard(Classifica classifica){
    char key; //valore del tasto che premerà l'utente
    clearscreen();
    printTop(classifica);
    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen(classifica);
        else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
    } while(true);
}


/*
    Author: Alice Benatti
    Parameters: lista -> lista contenente gli elementi salvati nella scoreboard.
    Return value: void
    Comments: Scorre la lista e stampa gli elementi contenuti in essa.
*/

void printTop(Classifica lista){
    cout << "\n\nHere is the scoreboard of our BEST player!\nAre you a part of it?\n\n";
    string aster = "*";
        int i = 0;
        while(lista.head != NULL && i < 9){
        if (i%2==0) color(Black, Purple);
        else color(Black, Red);
        lista.get_position(i);
        string tab = "\t";       
        color(Black, Purple);
        cout<<"[";
        color(Black,Bright_White);
        cout<<i+1;
        color(Black, Purple);
        cout<<"]"<<tab;
        color(Black,Light_Yellow);
        cout<<lista.head->nick<<tab;
        color(Black,Light_Aqua);
        cout<<lista.head->score<<endl;
        lista.head=lista.head->next;
        i++;
    }
 }
 