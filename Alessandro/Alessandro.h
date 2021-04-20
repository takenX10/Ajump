#ifndef ALESSANDRO_H
#define ALESSANDRO_H
/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
using namespace constants;
using namespace std;



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
        int current_id;
        int list_size;
        ptr_nodo_nemici head;
        Mappa *map;
        Player *player;

        // aggiorna il valore della variabile "move_direction" di ogni entita della lista
        void nuove_direzioni(void);

    public:
        Lista_nemici(Mappa *map, Player *p);

        // aggiunta in testa, quindi se si aggiungono solo nuovi nemici la lista
        // risulta sempre ordinata per le righe
        void aggiungi_nemico(Nemico enemy);

        // elimina il nemico nella colonna passata, se non e' presente nessun nemico
        // non fa niente
        void elimina_nemico(int colonna);
        
        // da chiamare ogni volta che si vuole far spawnare un nemico
        // P.S. si deve far spawnare max un nemico a "tick"
        int calcola_spawnpos_X(void);
        
        // da chiamare ogni volta che si vogliono far muovere i nemici, nel nostro caso ogni "tick"
        void muovi_nemici(void);
};

struct nodo_proiettili{
    int direction;
    int id;
    int x;
    int y;
    struct nodo_proiettili *next;
    struct nodo_proiettili *prev;
};
typedef nodo_proiettili *ptr_nodo_proiettili;

class Lista_proiettili{
    protected:
        ptr_nodo_proiettili head;
        int current_id;
    public:
        Lista_proiettili(void);

        void aggiungi_proiettile(int x, int y, int direction);

        void elimina_proiettile(int id);
        
        void muovi_proiettili(void);
};

#include "Alessandro.cpp"
#endif
