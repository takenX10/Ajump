#ifndef NEMICI_H
#define NEMICI_H
/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "Mappa.h"
#include "Player.h"
#include "costanti.hpp"
#include "Bullet.h"
using namespace constants;
using namespace std;
class Nemico{
public:
    int x, y; 
    int health;
    int damage;
    int kind_of_enemy; // 1-> Soldato semplice | 2-> Artigliere | 3-> Tank | 4-> Boss

public:
    Nemico(int pos_x, int pos_, int kind_of_enemy);
    char char_of_enemy();
    //Modifica la salute del nemico, se questa è minore di zero il nemico muore.
    void change_health(int value);
    //void change_damage(int value); //Mi sa mai usato questo metodo (?) controlla
    void update_position(int new_x, int new_y);
    int decide_kindOfEnemy(int level);

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
public:
    int current_id; // ultimo id nemico utilizzato
    int list_size; // dimensione della lista
    ptr_nodo_nemici head; // testa della lista
    Mappa *map;  // puntatore alla mappa
    Player *player;  // puntatore al player
    BulletList *proiettili;

    // aggiorna il valore della variabile "move_direction" di ogni entita della lista
    void nuove_direzioni(void);

public:
    Lista_nemici(Mappa *map, Player *p, BulletList *proiettili);

    // risulta sempre ordinata per righe, in testa l'elemento piu a sinistra
    // e in coda quello piu a destra
    void aggiungi_nemico(Nemico enemy);

    // elimina il nemico con l'id passato
    // se l'id non e' presente non avviene nulla
    void elimina_nemico(int id);

    //Riduce la vita del nemico nella colonna X; Se la vita scende a 0 lo elimina.
    //Se nella colonna non c'è nessuno non succede nulla.
    void danneggia_nemico_x(int x);

    // da chiamare ogni volta che si vogliono far muovere i nemici
    // massimo una volta a "tick"
    void muovi_nemici(void);


    // fa sparare tutti i nemici, posizionando il proiettile sotto il nemico
    void spara(void);

    // da chiamare ogni volta che si vuole far spawnare un nemico
    // P.S. si deve far spawnare max un nemico a "tick"
    int calcola_spawnpos_X(void);


};
#include "Nemici.cpp"
#endif