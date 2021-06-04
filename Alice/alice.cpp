/* 
@ Author: Alice Benatti

- uno che si occupa del game design (
    aumento di livello, statistiche e percentuali), 
    del main, 
    game over e classifica (8)
- schermata di inizio (premi invio per iniziare ecc....)
- classifica
- schermata game over
*/
#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
#include <cstdio>
#include <fstream>
#include <stdlib.h> // per interagire con il file .txt
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "../Main/main.cpp"

using namespace std;

//*********Costanti**********//
#define ENTER 13
#define SPACE 32
#define ESC 27
#define CHAR 30
#define UNDERSCORE 95
#define TOPNUMBER 4    //valore di x+1 righe stampate della classifica
    
//********************************
struct lista_classifica{
    char nick[CHAR];
    int score;
    struct lista_classifica *next;
};
typedef struct lista_classifica *plista;

class Classifica{
    public:
        plista head;
        char filename[30];
    public:
        Classifica(char filename[]){
            strcpy(this->filename, filename);
            this->head = this->get_file();
        }
        
        /*
            - apro il file Leaderboard.txt
            - prendo i valori e li salvo in lista
        */
        plista get_file(void){
            ifstream OpenFile;
            OpenFile.open(this->filename,ios::in);
            int c;
            plista Lista = new lista_classifica;
            plista tmp = Lista;
            plista tmp2 = NULL;
            int pass;
            string stringa;
            while (!OpenFile.eof()){
                getline(OpenFile, stringa, '\n');
                strcpy(tmp->nick, stringa.substr(stringa.find(' ')+1, stringa.find(' ', 2)-2).c_str());
                tmp->score = stoi(stringa.substr(stringa.find(' ', 2)+1, stringa.find('\n')));
                
                tmp2 = new lista_classifica;
                tmp->next = tmp2;
                tmp = tmp2;
                tmp->next = NULL;
            }
            OpenFile.close();
            return Lista;
        }
        /* 
            aggiungo alla lista nel punto desiderato
            - salvo in lista new_val i nuovi valori
            - scorro la lista e trovo il punto di inserimento
            - creo tmp aggiungo in testa il nuovo elemento
            - allaccio le liste
        */
        void add_value(int score, char nick[]){
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
            salvo nel file Leaderboard.txt la lista inserendo la posizione in classifica
        */
        void save_file(){
            plista tmp = this->head;
            ofstream myfile;
            cout<<this->filename;
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
        
        plista get_position(int position){
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
};
typedef Classifica* lista;

//dichiarazione funzioni
void StartScreen(Classifica lista);
void GameOver(Classifica lista, int punti);
void Leaderboard(Classifica lista);
int PrintMap(Classifica lista); //da cancellare QUASI
void printTop(Classifica lista);

// ====== Main ======
int main(void){
    Classifica alice = Classifica("leaderboard.txt");
    color(Black, White);
    GameOver(alice, 320);
    //StartScreen(alice);  //decommentare
    
    return 0;
}

// ====== Schermata iniziale: titolo & menu' ======
void StartScreen(Classifica LBoard){
    clearscreen();
    char key;
    color(Black, Light_Yellow);
    printfile("name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER to play" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "              >> press ESC to exit" << endl;
    color(Black, Light_Green);
    do{
        key=getch();
        if (key==ENTER)PrintMap(LBoard);
        else if (key== 'C' || key=='c') Leaderboard(LBoard);
        else if (key==ESC){ clearscreen(); exit(0); }
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    }
    while (true);
}

// funzione di alex x fare partire il Gioco + navigabilità (se serve)
int PrintMap(Classifica LBoard){
    clearscreen();
    char key;
    cout << "Sei in PrintMap u.u" << endl;
    color(Black, White);
    cout << "\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen(LBoard);
        else if ((int)key==ESC) clearscreen();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
    return 0;
}

/* ====== Game Over ======
    - salvataggio nuovo punteggio in classifica
    - navigabilità 
*/
void GameOver(Classifica LBoard, int score){
    clearscreen();
    char key;
    char input[CHAR];
    int id;
    bool check = false;
    
    color(Red, Bright_White);
    printfile("gameover.txt");  //da scommentare
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        do {
            key=getch();
            if ((int)key == 'y' || (int)key == 'Y') {
                check = true;
                cout << "Insert ur nick: ";
                cin >> input;
                //apro il file e salvo i valori vecchi
                LBoard.get_file();
                LBoard.add_value(score, input);
                LBoard.save_file();
                cout << "Ur score has been saved u.u"<< endl;
            }
            else if ((int)key == 'n' || (int)key == 'N') {
                check = true;
                cout << "\n\n       >> press SPACE to return at home" << endl;
                do{
                    key=getch();
                    if ((int)key == SPACE) StartScreen(LBoard);
                    else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;  
                } while(true);
            }
            else{
                check = false;
                cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl; 
            }
        }while (check==false);
        cout << "           >> press C to view the leaderboard" << endl;
        cout << "\n\n       >> press SPACE to return at home" << endl;
        do{
            key=getch();
            if ((int)key == SPACE) StartScreen(LBoard);
            else if ((int)key == 'c' || (int)key == 'C') Leaderboard(LBoard);
            else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
        } while(true);
    } while(true);
}

/* ====== Classifica dei punteggi ======
    - lettura file Leaderboard.txt
    - stampa classifica di x posizioni
    - evidenzia eventuale nuovo salvataggio
*/
void Leaderboard(Classifica classifica){
    char key; //valore del tasto premuto dall'utente
    clearscreen();
    cout << "GG Sei nella classifica :D\n" << endl;
    
   // classifica.get_file();
    // print classifica con get_position
    printTop(classifica);

    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen(classifica);
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
}

// stampa classifica di x posizioni
void printTop(Classifica lista){
    string aster = "*";
    for (int i = 0; i <= TOPNUMBER; i++){
        if (i%2==0) color(Black, Purple);
        else color(Black, Red);
        lista.get_position(i);
        string tab = "\t";
        /* vedi con gli asterischi: 1*  Nome    Punteggio | 2**   Nome    Punteggio ...
        if (strlen(lista.head->nick)<=8) tab ="\t\t";
        if (aster == "*****") aster ="*";
        cout<< aster <<(i+1) <<") "<< lista.head->nick << tab << lista.head->score<< setw(5)<<"*"<<endl;
        aster+="*";*/ 
        
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
    }
 }
 