#ifndef NEMICI_H
#define NEMICI_H
/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "Proiettili.h"
using namespace constants;
using namespace std;

// da eliminare in seguito, e' un sample
class Nemico{
    public:
        int x;
        int y;
        int tipo;
        Nemico(int x=-1, int y=-1, int tipo=-1); 
};

struct nodo_nemici{
    Nemico entity;
    bool just_spawned;
    char old_char;
    int move_direction;
    int id;
    struct nodo_nemici *next;
    struct nodo_nemici *prev;
};
typedef nodo_nemici *ptr_nodo_nemici;

class Lista_nemici{
    protected:
        int current_id; // ultimo id nemico utilizzato
        int list_size; // dimensione della lista
        ptr_nodo_nemici head; // testa della lista
        Mappa *map;  // puntatore alla mappa
        Player *player;  // puntatore al player
        Lista_proiettili *proiettili;

        // aggiorna il valore della variabile "move_direction" di ogni entita della lista
        void nuove_direzioni(void);

    public:
        Lista_nemici(Mappa *map, Player *p, Lista_proiettili *proiettili);

        // risulta sempre ordinata per righe, in testa l'elemento piu a sinistra
        // e in coda quello piu a destra
        void aggiungi_nemico(Nemico enemy);

        // elimina il nemico con l'id passato
        // se l'id non e' presente non avviene nulla
        void elimina_nemico(int id);
        
        // da chiamare ogni volta che si vogliono far muovere i nemici
        // massimo una volta a "tick"
        void muovi_nemici(void);

        void spara(void);

        // da chiamare ogni volta che si vuole far spawnare un nemico
        // P.S. si deve far spawnare max un nemico a "tick"
        int calcola_spawnpos_X(void);


};
#include "Nemici.cpp"
#endif