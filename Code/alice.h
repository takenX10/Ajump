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
    public:
        Classifica(char filename[]);
        
        
        /*
            Author: Alice Benatti
            Parameters: void
            Return value: Lista contenente nomi e punteggi dei player in scoreboard.
            Comments: Leggo le stringhe del file finchè non giungo alla fine dello stesso.
        */

        plista get_file(void);


        /*
            Author: Alice Benatti
            Parameters: score -> punteggio fatto dal player.
                        nick -> nome del player.
            Return value: void
            Comments: Cerco nella lista il punto esatto in cui inserire il punteggio.
                      L'obiettivo è ovviamente quello di mantenere una lista ordinata decrescentemente.
        */

        void add_value(int score, char nick[]);

        /*
            Author: Alice Benatti
            Parameters: void
            Return value: void
            Comments: salvo nel file Leaderboard.txt la lista appena aggiornata.
        */

        void save_file();

        /*
            Author: Alice Benatti
            Parameters: position -> posizione in classifica di un elemento.
            Return value: Puntatore all'elemento cercato nella lista in cui sono salvati gli elementi in classifica.
            Comments: Scorro la lista di 'position' ottenendo l'elemento da me cercato. 
        */

        plista get_position(int position);
};
typedef Classifica* lista;

/*
    Author: Alice Benatti
    Parameters: LBoard -> Scoreboard
    Return value: void
    Comments: Schermata iniziale del gioco. Permette la visualizzazione della classifica e di iniziare la partita.
*/

void StartScreen(Classifica LBoard);



/*
    Author: Alice Benatti
    Parameters: LBoard -> Scoreboard 
    Return value: void
    Comments: La funzione permette l'avvio del gioco.
*/

//TODO: si potrebbe fare un file a parte per questa printmap(?) Essendo praticamente il vero main del gioco.
//TODO: ma passare il parametro LBoard è necessario(?) Non saprei come spiegarne il senso.

void PrintMap(Classifica LBoard);



/*
    Author: Alice Benatti
    Parameters: score -> punteggio ottenuto dal player che ha appena terminato la partita.
    Return value: void
    Comments: La funzione viene chiamata al termine della partita. 
              Permette di salvare il punteggio nella leaderboard, aggiornarla, e visualizzarla.
              L'utente può anche scegliere di non salvare il punteggio, uscendo così dal gioco.
*/

void GameOver(int score);



/*
    Author: Alice Benatti
    Parameters: classifica -> lista contenente la classifica.
    Return value: void
    Comments: Pulisce lo schermo e chiama una funzione che stamperà la classifica.
*/

void Leaderboard(Classifica classifica);



/*
    Author: Alice Benatti
    Parameters: lista -> lista contenente gli elementi salvati nella scoreboard.
    Return value: void
    Comments: Scorre la lista e stampa gli elementi contenuti in essa.
*/

void printTop(Classifica lista);
 

#include "alice.cpp"
#endif