#ifndef GIOCO_H
#define GIOCO_H
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "bonus.h"

class Game{
    private:
        bool end_game; // inizializzato a false
        Map *game_map;
        Player *p;
        BulletList *bullet;
        EnemyList *enemy;
        Bonus *bonus;
    public:
        /*  Author:         Alessandro Frau
            Parameters:     m -> puntatore alla mappa
                            p -> puntatore al player
                            bullet -> puntatore alla lista di proiettili
                            enemy -> puntatore alla lista di nemici
                            bon -> puntatore ai bonus
            Return value:   none
            Comments:       Costruttore della classe Game
        */
        Game(Map *m, Player *p, BulletList *bullet, EnemyList *enemy, Bonus *bon);

        /*  Author:         Alessandro Frau, Francesco Apollonio (Parte dei bonus e dell'aumento graduale della difficolta')
            Parameters:     void
            Return value:   void
            Comments:       Funzione eseguita da un thread, refresha la mappa aggiornando cio che e' printato in
                            console, e chiamando ogni tot tempo automaticamente tutte le funzioni che si occupano
                            di far muovere i nemici, farli sparare, far muovere i proiettili, far nascere nuovi nemici
                            e aggiornare la difficolta del gioco
        */
        void auto_print_map(void);
        
        /*  Author:         Alessandro Frau, Francesco Apollonio (parte dei proiettili speciali)
            Parameters:     void
            Return value:   void
            Comments:       Funzione eseguita da un thread, si occupa di attendere la pressione di un tasto da parte
                            del player, e fa cio che gli viene dato in input dal tasto (spara / fa muovere il player)
        */
        void key_listener(void);

        /*  Author:         Alessandro Frau
            Parameters:     value -> valore di end_game
            Return value:   void
            Comments:       setta il valore di end_game a value
        */
        void set_end_game(bool value);
};
#include "Game.cpp"
#endif