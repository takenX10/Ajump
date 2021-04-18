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

// da eliminare in seguito
class general_enemy{
public:
    int x, y; //Posizione
    int health;
    int damage;
    int kind_of_enemy; // 1-> Soldato semplice | 2-> Artigliere | 3-> Tank | 4-> Boss

public:                 //I valori '-1' servono solo per debug, vanno rimossi
    general_enemy(int pos_x = -1, int pos_y = -1, int kind_of_enemy = -1){
        this->x = pos_x;
        this->y = pos_y;
        this->kind_of_enemy = kind_of_enemy;
        // Dal tipo di nemico posso già sapere vita e danno; inutile prenderli come ulteriori parametri.
        if (kind_of_enemy == 1) { this->health = 50; this->damage = 50; }
        else if (kind_of_enemy == 2) { this->health = 100; this->damage = 100; }
        else if (kind_of_enemy == 3) { this->health = 150; this->damage = 150; }
        else { this->health = 200; this->damage = 200;}
    }
    /*
     * Questo metodo permette di modificare la salute attuale del nemico;
     * Il valore preso in input può essere sia positivo che negativo, seguono due scenari d'esempio.
     * value == +50 -> Il player prende un Malus che aumenta la vita di tutti i nemici nella mappa.
     * value == -50 -> Il player spara il nemico ottenendo una riduzione della sua vita.
     * value == -1000 -> Il player prende un bonus che riduce infinitamente la vita di tutti i nemici nella mappa: ottiene piazza pulita.
     */
    void change_health(int value){
        this->health += value;
    }
    // Stesso discorso di change_health: value può essere sia positivo che negativo.
    void change_damage(int value){
        this->damage += value;
    }
    void update_position(int new_x, int new_y){
        this->x = new_x;
        this->y = new_y;
    }
    //Questo metodo ritorna il carattere char rappresentante il tipo di nemico in questione nella mappa.
    //E' ancora da decidere qualche char rappresenterà quale nemico, dunque simbolicamente per ora ritornano i char 1, 2, 3, 4.
    char char_rapresentation(){
        if (kind_of_enemy == 1) return '1';
        else if (kind_of_enemy == 2) return '2';
        else if (kind_of_enemy == 3) return '3';
        else return '4';
    }

};

struct nodo_nemici{
    general_enemy entity;
    bool just_spawned;
    char old_char;
    int move_direction;
    struct nodo_nemici *next;
    struct nodo_nemici *prev;
};
typedef nodo_nemici *ptr_nodo_nemici;

class Lista_nemici{
    protected:
        
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
        void aggiungi_nemico(general_enemy enemy);

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
