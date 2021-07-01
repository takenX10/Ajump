#ifndef BONUS_H
#define BONUS_H

#include <iostream>
#include "Mappa.h"
#include "Player.h"
#include "Proiettili.h"
#include "Nemici.h"
#include "time.h"
#include "costanti.hpp"
#include "Gioco.h"

using namespace constants;
using namespace std;

struct nodo_bonus{
    int kind_of_bonus;
    int x;
    int y;
    int id;
    struct nodo_bonus *next;
    struct nodo_bonus *prev;
};
typedef nodo_bonus *ptr_bonus;


class Bonus{
protected:
    ptr_bonus head;
    Mappa *map;
    Player *player;
    Lista_nemici *nemico;
    Lista_proiettili *proiettili;
    int current_id;

public:
    //Parametro utile per evitare lo spawn di più bonus nello stesso momento ( punto della mappa )
    int last_spawn_height;
    Bonus(Mappa *map, Player *player, Lista_nemici *nemici, Lista_proiettili *proiettili);

    //aggiunge un bonus in lista
    void aggiungi_bonus();

    //elmina il bonus dalla mappa
    void rimuovi_bonus(int id);


    //esegue il bonus e lo elimina dalla mappa in base alla posizione ricevuta
    void esegui_bonus(int kind_of_bonus, int x, int y);

    //Restituisce il carattere rappresentante il bonus
    char char_of_bonus(int kind_of_bonus);


};





//classe
//aggiungi vita play
//modifica danno player
//esplodi tutti i nemici
//hint capirai quando lo userai 
//sotto al bonus c'è uno spazio vuoto 


#include "bonus.cpp"
#endif