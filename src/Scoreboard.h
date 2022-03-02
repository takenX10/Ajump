#ifndef ALICE_H_
#define ALICE_H_
#include "costanti.hpp"
using namespace std;


struct scoreboard_list{
    char nick[CHAR_VALUE];
    int score;
    struct scoreboard_list *next;
};
typedef struct scoreboard_list *ptr_scoreboard_list;

class Scoreboard{
    public:
        ptr_scoreboard_list head;
        char filename[100];
    public:
        /*  Author:         Alice Benatti
            Parameters:     filename -> il nome del file dove e' salvata la classifica
            Return value:   void
            Comments:       Costruttore della classe Scoreboard
        */
        Scoreboard(char filename[]);
        
        
        /*  Author:         Alice Benatti
            Parameters:     void
            Return value:   Lista contenente nomi e punteggi dei player in scoreboard.
            Comments:       Leggo le stringhe del file finchè non giungo alla fine dello stesso.
        */
        ptr_scoreboard_list get_file(void);


        /*  Author:         Alice Benatti
            Parameters:     score -> punteggio fatto dal player.
                            nick -> nome del player.
            Return value:   void
            Comments:       Cerco nella lista il punto esatto in cui inserire il punteggio.
                            L'obiettivo è ovviamente quello di mantenere una lista ordinata decrescentemente.
        */
        void add_value(int score, char nick[]);

        /*  Author:         Alice Benatti
            Parameters:     void
            Return value:   void
            Comments:       salvo nel file Leaderboard.txt la lista appena aggiornata.
        */
        void save_file();

        /*  Author:         Alice Benatti
            Parameters:     position -> posizione in classifica di un elemento.
            Return value:   Puntatore all'elemento cercato nella lista in cui sono salvati gli elementi in classifica.
            Comments:       Scorro la lista di 'position' ottenendo l'elemento da me cercato. 
        */
        ptr_scoreboard_list get_position(int position);
};

 

#include "Scoreboard.cpp"
#endif