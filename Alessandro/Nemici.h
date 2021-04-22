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

class Nemico{
public:
    int x, y; //Posizione
    int health;
    int damage;
    int kind_of_enemy; // 1-> Soldato semplice | 2-> Artigliere | 3-> Tank | 4-> Boss

public:
    Nemico(int pos_x, int pos_y);
    char char_of_enemy();
    /*
    * Questo metodo permette di modificare la salute attuale del nemico;
    * Il valore preso in input può essere sia positivo che negativo, seguono due scenari d'esempio.
    * value == +50 -> Il player prende un Malus che aumenta la vita di tutti i nemici nella mappa.
    * value == -50 -> Il player spara il nemico ottenendo una riduzione della sua vita.
    * value == -1000 -> Il player prende un bonus che riduce infinitamente la vita di tutti i nemici nella mappa: ottiene piazza pulita.
    */
    void change_health(int value);
    // Stesso discorso di change_health: value può essere sia positivo che negativo.
    void change_damage(int value);
    void update_position(int new_x, int new_y);
    void decide_kindOfEnemy(int level);

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
    //elimina nemico nella colonna x
    void elimina_nemico_x(int x);

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