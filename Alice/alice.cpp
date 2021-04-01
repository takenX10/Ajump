/* 
@ Author: Alice Benatti

- uno che si occupa del game design (
    aumento di livello, statistiche e percentuali), 
    del main, 
    game over e classifica (8)
- i bonus li iListaementa quello che ha meno roba da fare (ce ne accorgeremo sul momento)

- schermata di inizio (premi invio per iniziare ecc....)
- classifica
- schermata game over
*/
#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include "../Main/main.cpp"

using namespace std;

#define ENTER 13
#define SPACE 32
#define ESC 27
#define CHAR 30
#define UNDERSCORE 95
#define maxSaved 65*40 // 40 maxListaayer salvati

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
            - apro il file
            - prendo i valori e li salvo in lista
            - trovo il punto giusto dove inserire il nuovo punteggio delListaayer
            - aggiungo ilList 
            - stampo la Top(X) dove X num da settare in base a quanti giocatori vogliamo visualizzare
        */
        plista get_file(void){
            FILE *OpenFile;
            OpenFile = fopen (this->filename, "r");
            int c;
            plista Lista = new lista_classifica;
            plista tmp = Lista;
            plista tmp2 = NULL;
            int pass;
            while (feof(OpenFile)){
                cout << "devo scannare" << endl;
                fscanf(OpenFile, "%d", pass);
                fscanf(OpenFile, "%s", tmp->nick);
                fscanf(OpenFile, "%d", tmp->score);
                fscanf(OpenFile, "\n", c);
                cout << "ho fatto tutti fscanf" << endl; //da togliere
                if (c == '\n') {
                    tmp2 = new lista_classifica;
                    tmp->next = tmp2;
                    tmp = tmp2;
                }else{
                    tmp->next = NULL;
                }
            }
            fclose(OpenFile);
            return Lista;
        
        }
        
        /* 
            aggiungo alla lista nel punto desiderato
            - salvo la lista
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
                    if (tmp->next->score < new_val->score){
                        new_val->next = tmp->next;
                        tmp->next = new_val;
                        exit = true;
                    }
                }
                if (exit == false){
                    tmp->next = new_val;
                    new_val->next = NULL;
                }
            }
        }

        void save_file(void){
            plista tmp = this->head;
            FILE* myfile = fopen(this->filename, "a");
            int i = 1;
            while (tmp != NULL){         
                fprintf(myfile, "%d %s %d\n", i, tmp->nick, tmp->score);
                tmp = tmp->next;
                i++;
            }
            fclose(myfile);
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

void StartScreen();
void GameOver(plista lista, int punti);
void Leaderboard();
int PrintMap(); //da cancellare QUASI


int main(){
    Classifica alice = Classifica("leaderboard.txt");
    color(Black, White);
    plista aposessuale = alice.get_position(1);
    cout<<aposessuale->score;
    //GameOver(alice, 883);
   // StartScreen();  //decommentare
    return 0;
}

// ====== Schermata iniziale: titolo & menù ======
void StartScreen(){
    clearscreen();
    char key;
    color(Black, Yellow);
  //  printfile("name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER toListaay" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "              >> press ESC to exit" << endl;
    color(Black, Light_Green);
    do{
        key=getch();
        if (key==ENTER)PrintMap();
        else if (key== 'C' || key=='c') Leaderboard();
        else if (key==ESC){ clearscreen(); exit(0); }
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    }
    while (true);
}

// funzione di alex x fare partire il Gioco + cose
int PrintMap(){
    clearscreen();
    char key;
    cout << "Sei in PrintMap u.u" << endl;
    color(Black, White);
    cout << "\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen();
        else if ((int)key==ESC) clearscreen();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
    return 0;
}

// ====== Game Over ======
void GameOver(plista LBoard, int score){
    clearscreen();
    char key;
    char input[CHAR];
    int id;
    bool check = false;
    
    color(Red, Bright_White);
  //  printfile("gameover.txt");  //da scommentare
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        do {
            key=getch();
            if ((int)key == 'y' || (int)key == 'Y') {
                check = true;
                cout << "Insert ur nick: ";
                cin >> input;
                    
                // Salvo la lista ordinata in modo da stamparla giusta :D
            }
            else if ((int)key == 'n' || (int)key == 'N') {
                check = true;
                cout << "\n\n       >> press SPACE to return at home" << endl;
                do{
                    key=getch();
                    if ((int)key == SPACE) StartScreen();
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
            if ((int)key == SPACE) StartScreen();
            else if ((int)key == 'c' || (int)key == 'C') Leaderboard();
            else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
        } while(true);
    } while(true);
}

// ====== Classifica dei punteggi ======
void Leaderboard(){
    char key;
    clearscreen();
    cout << "GG Sei nella classifica :D\n" << endl;
 //   printfile("leader-out.txt");
    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
}
