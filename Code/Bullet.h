#ifndef PROIETTILI_H
#define PROIETTILI_H

#include<iostream>
#include "Mappa.h"
#include "Player.h"
#include "costanti.hpp"
#include "Gioco.h"
using namespace constants;
using namespace std;

struct BulletNode{
    int direction;
    int id;
    int x;
    int y;
    char old_char;
    bool already_moved;
    int damage; //dipende dal nemico che lo spara
    struct BulletNode *next;
    struct BulletNode *prev;
};
typedef BulletNode *ptr_bullet_node;

class BulletList{
protected:
    ptr_bullet_node head;
    Mappa *map;
    Player *player;
    int current_id;
    int special_bullet; //Numero di Proiettili speciali a disposizione; questi si ottengono con un Bonus
    int damage_enemy_x = -1; // Questo parametro varia indicando la colonna nella quale è presente un nemico da danneggaire.


public:

    /*  Author:         Alessandro Frau
        Parameters:     map -> puntatore alla mappa
                        p -> puntatore al player
        Return value:   void
        Comments:       Costruttore
    */
    BulletList(Mappa *map, Player *p);
   
    /*  Author:         Alessandro Frau (Parte logica), Francesco Apollonio (Parte di who_shot)
        Parameters:     x -> cordinata x in cui deve uscire il proiettile
                        y -> cordinata y in cui deve uscire il proiettile
                        direction -> la direzione in cui si sposta il proiettile (SOPRA o SOTTO)
                        who_shot -> Il codice del nemico che ha sparato (COD_BOSS, COD_TANK, ...)
        Return value:   void
        Comments:       Funzione che aggiunge un proiettile alla lista
                        - La lista e' ordinata per righe, quindi l'aggiunta
                          avviene nella posizione corretta
    */  
    void add_bullet(int x, int y, int direction, int who_shot);

    /*  Author:         Alessandro Frau
        Parameters:     id -> id del proiettile da eliminare
        Return value:   void
        Comments:       Funzione che si occupa di eliminare il proiettile con l'id passato
    */
    void delete_bullet(int id);

    /*  Author:         Alessandro Frau
        Parameters:     x -> cordinata x del proiettile
                        y -> cordinata y del proiettile
                        old_char -> valore che verra' settato come nuovo old_char del proiettile
        Return value:   vecchio old_char del proiettile
        Comments:       setta l'old_char del proiettile a coordinate x, y, e ne restituisce l'old_char prima di essere modificato
    */
    char set_and_retrieve(int x, int y, int old_char);

    /*  Author:         Alessandro Frau
        Parameters:     void
        Return value:   void
        Comments:       Funzione che fa sparare un proiettile a tutti i nemici contemporaneamente
    */
    void shoot_bullet(void);

    /*  Author:         Francesco Apollonio 
        Parameters:     void
        Return value:   int
        Comments:       Funzione che restituisce il numero di proiettili speaciali disponibili.
    */

    int get_special_bullet(void);


    /*  Author:         Francesco Apollonio 
        Parameters:     int
        Return value:   void
        Comments:       Funzione che setta il numero di proiettili speaciali disponibili.
                        Viene chiamata nel momento in cui il player prende il bonus "proiettili speciali"
                        Il numero che viene settato è predefinito.
    */

    void set_special_bullet(int number);


    /*  Author:         Francesco Apollonio 
        Parameters:     void
        Return value:   int
        Comments:       La funzione restituisce la colonna sulla quale è presente un nemico da danneggiare.
                        Se nessun nemico dev'essere danneggiato il suo valore di default è -1.
    */

    int get_damage_enemy_x(void);



    /*  Author:         Francesco Apollonio 
        Parameters:     int
        Return value:   void
        Comments:       La funzione modifica il parametro identificando così una colonna sulla quale
                        è presente un nemico da danneggiare.
    */

    void set_damage_enemy_x(int x);


    /*  Author:         Alessandro Frau (Parte logica), Francesco Apollonio (Parte legata al danno in base al tipo di nemico)
        Parameters:     void
        Return value:   void
        Comments:       - La funzione si occupa di muovere tutti i proiettili nelle giuste
                          posizioni, 
                        - La testa e' il proiettile piu in alto
                        - La lista e' ordinata per righe
    */
    void move_bullet(void);

    

};

#include "Bullet.cpp"
#endif
