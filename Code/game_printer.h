
#ifndef GAME_PRINTER_H_
#define GAME_PRINTER_H_

#include "Scoreboard.h"

/*  Author:         Alice Benatti
    Parameters:     lista -> lista contenente gli elementi salvati nella scoreboard.
    Return value:   void
    Comments:       Scorre la lista e stampa gli elementi contenuti in essa.
*/
void print_top(Scoreboard lista);

/*  Author:         Alice Benatti
    Parameters:     score -> punteggio ottenuto dal player che ha appena terminato la partita.
    Return value:   void
    Comments:       La funzione viene chiamata al termine della partita. 
                    Permette di salvare il punteggio nella leaderboard, aggiornarla, e visualizzarla.
                    L'utente può anche scegliere di non salvare il punteggio, uscendo così dal gioco.
*/
void game_over(int score);

/*  Author:         Alice Benatti
    Parameters:     void 
    Return value:   void
    Comments:       La funzione permette l'avvio del gioco.
*/
void print_map(void);

/*  Author:         Alice Benatti
    Parameters:     classifica -> lista contenente la classifica.
    Return value:   void
    Comments:       Pulisce lo schermo e chiama una funzione che stamperà la classifica.
*/
void leaderboard(Scoreboard classifica);

/*  Author:         Alice Benatti
    Parameters:     LBoard -> Scoreboard
    Return value:   void
    Comments:       Schermata iniziale del gioco. Permette la visualizzazione della classifica e di iniziare la partita.
*/
void start_screen(Scoreboard LBoard);
#include "game_printer.cpp"
#endif