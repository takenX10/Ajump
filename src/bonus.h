#ifndef BONUS_H
#define BONUS_H

#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "time.h"
#include "costanti.hpp"
#include "Game.h"

using namespace constants;
using namespace std;

struct bonus_node{
    int kind_of_bonus;
    int x;
    int y;
    int id;
    struct bonus_node *next;
    struct bonus_node *prev;
};
typedef bonus_node *ptr_bonus;


class Bonus{
protected:
    ptr_bonus head;
    Map *map;
    Player *player;
    EnemyList *enemy;
    BulletList *bullets;
    int current_id;
    int last_spawn_height;    //Parametro utile ad evitare lo spawn di più bonus nello stesso punto (livello) della mappa.

public:
    /*  Author:         Francesco Apollonio
        Parameters:     map -> mappa del gioco, necessaria per determinare i punti di spawn
                        player -> parametro necessario per modificare parametri del player come 'Health points'
                        nemici -> parametro necessario per operazioni sui nemici nel caso del bonus 'bomba'
                        proiettili -> parametro necessario per operazioni sui proiettili nel caso del bnonus 'proiettili speciali'
        Return value:   void
        Comments:       Costruttore.
    */

    Bonus(Map *map, Player *player, EnemyList *nemici, BulletList *proiettili);



    /*  Author:         Francesco Apollonio
        Parameters:     void
        Return value:   void
        Comments:       Spawn dei bonus ed aggiunta dei loro valori nella lista che li tiene in memoria.

        Spiegazione intuitiva dell'algoritmo che determina la posizione dello spawn del bonus:
        Partendo dal centro, mi sposto prima a destra e poi a sinistra finchè non
        trovo una zona della mappa che soddisfi i miei parametri per lo spawn del bonus;
        uno spazio vuoto con sotto almeno due basi (in modo che il player possa arrivarci agevolmente)
        
    */

    void add_bonus();

    

    /*  Author:         Francesco Apollonio
        Parameters:     int id -> Id del bonus da eliminare. Ogni bonus ha un ID unico, utile alla sua identificazione.
        Return value:   void
        Comments:       Ricerca un bonus tramite il suo ID e lo rimuove dalla lista.
    */

    void remove_bonus(int id);



    /*  Author:         Francesco Apollonio
        Parameters:     kind_of_bonus -> Tipologia del bonus da eseguire; Ogni bonus ha un codice corrispondente utile ad identificarlo.
                        x, y -> Parametri indicanti la posizione del bonus.
        Return value:   restituisce il valore di end_game
        Comments:       La funzione esegue il bonus, eseguendo gli 'effetti' corrispondenti; Quindi elimina il bonus dalla mappa e della lista (richiamando la funzione di cui sopra)
    */

    bool exec_bonus(int kind_of_bonus, int x, int y);



    /*  Author:      Francesco Apollonio
        Parameters:     kind_of_bonus -> Codice identificativo del tipo di bonus.
        Return value:   char
        Comments:       La funzione restituisce il carattere, che verrà stampato nella mappa, del bonus corrisponente. 
    */

    char char_of_bonus(int kind_of_bonus);



    /*  Author:         Francesco Apollonio
        Parameters:     value -> valore rappresentante l'altezza (nella mappa) in cui è stato fatto spawnare l'ultimo bonus.
        Return value:   void
        Comments:       il setting di questo parametro è utile ad evitare lo spawn di più bonus nello stesso punto (livello) della mappa. 
    */

    void set_last_spawn_height(int value);



    /*  Author:         Francesco Apollonio
        Parameters:     void
        Return value:   int
        Comments:       La funzione restituisce il valore del parametro 'last_spawn_height' 
    */

    int get_last_spawn_height(void);


};

#include "Bonus.cpp"
#endif