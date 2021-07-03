#ifndef ALICE_H_
#define ALICE_H_
#include "costanti.hpp"
using namespace std;


struct lista_classifica{
    char nick[CHAR_VALUE];
    int score;
    struct lista_classifica *next;
};
typedef struct lista_classifica *plista;

class Classifica{
    public:
        plista head;
        char filename[100];
        int registered_scores; // Numero di elementi salvati.
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

        int get_scoreboard_lenght(void);
        
        plista get_position(int position);
};
typedef Classifica* lista;

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
void Leaderboard(Classifica classifica, int scoreboard_lenght);

// stampa classifica di x posizioni
void printTop(Classifica lista, int scoreboard_lenght);
 

#include "alice.cpp"
#endif