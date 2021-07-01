#ifndef ALICE_H_
#define ALICE_H_
using namespace std;

//*********Costanti**********//
#define ENTER 13
#define SPACE 32
#define ESC 27
#define CHAR 30
#define UNDERSCORE 95
#define TOPNUMBER 4    //valore di x+1 righe stampate della classifica
#define patchFile "C:\\Users\\theas\\Documents\\GitHub\\Ajump\\Alice\\leaderboard.txt"
    
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
        char filename[100];
    public:
        Classifica(char filename[]);
        
        /*
            - apro il file Leaderboard.txt
            - prendo i valori e li salvo in lista
        */
        plista get_file(void);
        /* 
            aggiungo alla lista nel punto desiderato
            - salvo in lista new_val i nuovi valori
            - scorro la lista e trovo il punto di inserimento
            - creo tmp aggiungo in testa il nuovo elemento
            - allaccio le liste
        */
        void add_value(int score, char nick[]);
        /*
            salvo nel file Leaderboard.txt la lista inserendo la posizione in classifica
        */
        void save_file();
        
        plista get_position(int position);
};
typedef Classifica* lista;

// ====== Main ======
/*int main(){
    Classifica alice = Classifica("C:\\Users\\alice\\Documents\\GitHub\\Ajump\\Alice\\leaderboard.txt");
    color(Black, White);
    GameOver(alice, 320);
    //StartScreen(alice);  //decommentare
    
    return 0;
}*/

// ====== Schermata iniziale: titolo & menu' ======
void StartScreen(Classifica LBoard);

// funzione di alex x fare partire il Gioco + navigabilità (se serve)
void PrintMap(Classifica LBoard);

/* ====== Game Over ======
    - salvataggio nuovo punteggio in classifica
    - navigabilità 
*/
void GameOver(int score);

/* ====== Classifica dei punteggi ======
    - lettura file Leaderboard.txt
    - stampa classifica di x posizioni
    - evidenzia eventuale nuovo salvataggio
*/
void Leaderboard(Classifica classifica);

// stampa classifica di x posizioni
void printTop(Classifica lista);
 

#include "alice.cpp"
#endif