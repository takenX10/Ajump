#ifndef NEMICI_H
#define NEMICI_H

#include "Map.h"
#include "Player.h"
#include "Bullet.h"

class Enemy{
    private:
        int x, y; 
        int health;
        int damage;
        int kind_of_enemy; // 1-> Soldato semplice | 2-> Artigliere | 3-> Tank | 4-> Boss

    public:
        /*  Author:         Alessandro Frau
            Parameters:     pos_x -> cordinata x del nemico
                            pos_y -> cordinata y del nemico
                            kind_of_enemy -> tipo di nemico (COD_TANK, COD_ARTIGLIERE, ....)
            Return value:   void
            Comments:       Costruttore della classe Enemy
        */
        Enemy(int pos_x, int pos_, int kind_of_enemy);
        
        /*  Author:         Francesco Apollonio
            Parameters:     void
            Return value:   carattere del nemico 
            Comments:       Restituisce il carattere legato al nemico
        */
        char char_of_enemy();

        /*  Author:         Francesco Apollonio
            Parameters:     value -> valore da aggiungere alla vita del nemico
            Return value:   void
            Comments:       Aggiunge il valore passato alla vita del nemico
        */
        void change_health(int value);
        
        /*  Author:         Alessandro Frau
            Parameters:     new_x -> nuova cordinata x del nemico
                            new_y -> nuova cordinata y del nemico
            Return value:   void
            Comments:       Cambia le cordinate del nemico con quelle passate
        */
        void update_position(int new_x, int new_y);


        /*  Author:         Francesco Apollonio
            Parameters:     level -> il livello corrente, serve per determinare la difficolta
            Return value:   Tipo di nemico estratto
            Comments:       Funzione che si occupa di restituire il tipo di nemico far spawnare, se il gioco supera una livello
                            La difficolta diventa estrema, quindi tutti i nemici diventeranno di tipo boss
        */
        int decide_kind_of_enemy(int level);
        
        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   this->x
            Comments:       funzione che restituisce la cordinata x del nemico
        */
        int get_x(void);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   this->y
            Comments:       funzione che restituisce la cordinata y del nemico
        */
        int get_y(void);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   this->health
            Comments:       funzione che restituisce la vita del nemico
        */
        int get_health(void);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   this->kind_of_enemy
            Comments:       funzione che restituisce il tipo del nemico
        */
        int get_kind_of_enemy(void);
};

struct enemy_node{
    Enemy entity;
    bool just_spawned;
    char old_char;
    int move_direction;
    int id;
    struct enemy_node *next;
    struct enemy_node *prev;
};
typedef enemy_node *ptr_enemy_node;

class EnemyList{
    private:
        int current_id; // ultimo id nemico utilizzato
        int list_size; // dimensione della lista
        ptr_enemy_node head; // testa della lista
        Map *map;  // puntatore alla mappa
        Player *player;  // puntatore al player
        BulletList *proiettili;

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   void
            Comments:       Aggiorna il valore della variabile move_direction per ogni nemico della lista
        */
        void new_directions(void);

    public:
        /*  Author:         Alessandro Frau
            Parameters:     map -> puntatore alla mappa
                            p -> puntatore al player
                            proiettili -> puntatore alla classe che gestisce la lista di proiettili
            Return value:   void
            Comments:       Costruttore della classe EnemyList
        */
        EnemyList(Map *map, Player *p, BulletList *proiettili);

        /*  Author:         Alessandro Frau
            Parameters:     enemy -> Classe nemico da aggiungere
            Return value:   void
            Comments:       Aggiunge un nemico alla lista di nemici, mantenendo delle caratteristiche:
                            - La lista e' ordinata per colonne (in testa il nemico piu a sinistra e in coda quello piu a destra)
                            - Si da per scontato che nella colonna non sia presente nessun altro nemico, questo perche'
                            per decidere la cordinata x del nemico si deve utilizzare la funzione get_spawnpos_x().
        */
        void add_enemy(Enemy enemy);

        /*  Author:         Alessandro Frau
            Parameters:     id -> id del nemico da eliminare
            Return value:   void
            Comments:       Elimina dalla lista di nemici quello con l'id passato, se non e' presente neanche un nemico con quell'id
                            non elimina nulla.
        */
        void delete_enemy(int id);

        /*  Author:         Francesco Apollonio
            Parameters:     cordinata x del nemico
            Return value:   void
            Comments:       Funzione che riduce la vita del nemico alla cordinata x passata, in base al danno del proiettile del player.
        */
        void damage_enemy_x(int x);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   restituisce il valore di end_game
            Comments:       Funzione che fa muovere tutti i nemici all'unisono verso il player, facendo in
                            modo che nessun nemico sia nella stessa colonna dell'altro. Questa funzione deve
                            venire chiamata massimo una volta a tick.
        */
        bool move_enemy(void);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   restituisce il valore di end_game
            Comments:       Fa sparare a tutti i nemici all'unisono un proiettile
        */
        bool shoot(void);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   Cordinata in cui il nemico puo spawnare 
            Comments:       Restituisce la cordinata x in cui il nemico puo spawnare, -1 se non ci sono spazi disponibili
        */
        int calculate_spawnpos_x(void);
        
        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   this->head
            Comments:       funzione che restituisce testa della lista
        */
        ptr_enemy_node get_head(void);
};
#include "Enemy.cpp"
#endif