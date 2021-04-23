#ifndef PROIETTILI_H
#define PROIETTILI_H

#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
using namespace constants;
using namespace std;

struct nodo_proiettili{
    int direction;
    int id;
    int x;
    int y;
    char old_char;
    bool already_moved;
    int damage; //dipende dal nemico che lo spara
    struct nodo_proiettili *next;
    struct nodo_proiettili *prev;
};
typedef nodo_proiettili *ptr_nodo_proiettili;

class Lista_proiettili{
protected:
    ptr_nodo_proiettili head;
    Mappa *map;
    Player *player;
    int current_id;
public:
    int elimina_nemico_x = -1;
    Lista_proiettili(Mappa *map, Player *p);

    // funzione che aggiunge un proiettile alla lista
    // la lista e' ordinata per righe, quindi la funzione si occupa di
    // aggiungere il proiettile nella posizione corretta

    //Who shot: devo sapere chi ha sparato per sapere quanto danno farà il proiettile.    
    void aggiungi_proiettile(int x, int y, int direction, int who_shot);


    void elimina_proiettile(int id);

    // Funzione che fa sparare il player, posizionando il proiettile sopra il player
    void spara_player(void);

    // setta l'old_char del proiettile a coordinate x, y, e ne restituisce l'old_char prima di essere modificato
    char set_and_retrieve(int x, int y, int old_char);

    // funzione che si occupa di far muovere tutti i proiettili nelle giuste posizioni
    // la testa e' il proiettile piu in alto
    // la lista e' ordinata per righe

    void muovi_proiettili(void);

};

#include "Proiettili.cpp"
#endif
