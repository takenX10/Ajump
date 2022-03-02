#ifndef MAPPA_H
#define MAPPA_H
#include "costanti.hpp"
using namespace constants;
struct map_node{
    char row[ROW_DIM];
    long int num_row;    // identificatore univoco riga
    map_node* prev;
    map_node* next;
};
typedef map_node* ptr_map_node;
class Map{
    private:
        ptr_map_node map_head;
        ptr_map_node map_tail;
        int map_height;
        int map_width;
        int total_height;

    public:
        /*  Author:         Alex Lorenzato
            Parameters:     larghezza e altezza mappa (inteso come righe da visualizzare nella singola schermata)
            Return value:   none
            Comments:       inizializzazione mappa, vengono riempiti i primi map_height piani con dele piattaforme
        */
        Map(int map_height = 0, int map_width = 0);
        
        /*  Author:         Alex Lorenzato
            Parameters:     none
            Return value:   none
            Comments:       crea un piano riempiendolo con le piattaforme, distingue i casi checkpoint/ground floor/riga vuota/riga con piattaforme
        */
        void new_row(void);
        
        /*  Author:         Alex Lorenzato
            Parameters:     punto piu in alto da visualizzare, vita player, altezza massima raggiunta e numero di proiettili speciali
            Return value:   none
            Comments:       gestione della stampa della mappa
        */
        void print_map(int top_line, int vita, int total_height, int bullets);
        
        /*  Author:         Alex Lorenzato
            Parameters:     numero riga cercata
            Return value:   puntatore alla riga cercata
            Comments:       getter di una riga
        */
        ptr_map_node get_row(int n);

        /*  Author:         Alex Lorenzato
            Parameters:     carattere da scrivere e posizione in cui scriverlo
            Return value:   none
            Comments:       scrive un carattere in una posizione della mappa
        */
        void set_char(int x, int y, char c);
        
        /*  Author:         Alex Lorenzato
            Parameters:     void
            Return value:   larghezza della mappa
            Comments:       restituisce la larghezza della mappa
        */
        int get_width(void);
        
        /*  Author:         Alex Lorenzato
            Parameters:     void
            Return value:   altezza della mappa
            Comments:       restituisce l'altezza della mappa
        */
        int get_height(void);
        
        /*  Author:         Alex Lorenzato
            Parameters:     void
            Return value:   altezza totale della mappa
            Comments:       restituisce l'altezza totale della mappa
        */
        int get_total_height(void);
};
#include "Map.cpp"
#endif