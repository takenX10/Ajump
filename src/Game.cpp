#include <iostream>
#include <windows.h>
#include <conio.h>
#include "ExternalFunctions.h"
#include "costanti.hpp"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "bonus.h"
#include "Scoreboard.h"

using namespace std;
using namespace constants;

/*  Author:         Alessandro Frau, Francesco Apollonio
    Parameters:     m -> puntatore alla mappa
                    p -> puntatore al player
                    bullet -> puntatore alla lista di proiettili
                    enemy -> puntatore alla lista di nemici
                    bon -> puntatore ai bonus
    Return value:   void
    Comments:       Costruttore della classe Game
*/
Game::Game(Map *m, Player *p, BulletList *bullet, EnemyList *enemy, Bonus *bon){
    this->game_map = m;
    this->end_game= false;
    this->p = p;
    this->bullet = bullet;
    this->enemy = enemy;
    this->bonus = bon;
}

/*  Author:         Alessandro Frau, Francesco Apollonio (Parte dei bonus e dell'aumento graduale della difficolta')
    Parameters:     void
    Return value:   void
    Comments:       Funzione eseguita da un thread, refresha la mappa aggiornando cio che e' printato in
                    console, e chiamando ogni tot tempo automaticamente tutte le funzioni che si occupano
                    di far muovere i nemici, farli sparare, far muovere i proiettili, far nascere nuovi nemici
                    e aggiornare la difficolta del gioco
*/
void Game::auto_print_map(){

    int counter_enemy_movement = 0;         // decide quando far muovere i nemici
    int counter_enemy_spawn = 0;            // decide quando far nascere i nemici
    int counter_bullet_movement = 0;        // decide quando far muovere i proiettili
    int counter_fire = 0;                   // decide quando far sparare i nemici
    // I quattro parametri seguenti possono essere modificati, mantenendo i rapporti sottostanti, per aumentare la difficoltà del gioco gradualmente
    int bullet_movement_speed = 1;
    int enemy_movement_speed = bullet_movement_speed * 10;
    int enemy_spawn_speed = enemy_movement_speed + 100;
    int enemy_fire_rate = bullet_movement_speed * 30;
    int difficulty = STEP_DIFFICOLTA; //Questo variabile stabilisce ogni quante righe viene aumentato il livello di difficoltà
    while(!this->end_game){       

        //Il seguente IF permette l'aumento graduale della difficoltà, andando a modificare
        //la velocità di spawn dei nemici, e quindi il numero di nemici da affrontare contemporaneamente.
        if(this->p->getY() > 1){
            if((this->p->getY() - 1) % difficulty == 0 && enemy_spawn_speed - 10 > enemy_movement_speed){
            counter_enemy_spawn = 0;
            enemy_spawn_speed = (enemy_spawn_speed - 10);
            difficulty += STEP_DIFFICOLTA;
            }
        }
        Sleep(REFRESH_RATE);
        
        if(counter_bullet_movement == bullet_movement_speed){
            this->end_game = this->bullet->move_bullet() || this->end_game;
            if(this->bullet->get_damage_enemy_x() != -1){
                this->enemy->damage_enemy_x(this->bullet->get_damage_enemy_x());
                this->bullet->set_damage_enemy_x(-1);
            }
            counter_bullet_movement = -1;
        }

        if(counter_fire == enemy_fire_rate){
            this->end_game = this->enemy->shoot() || this->end_game;
            counter_fire = -1;
        }

        if(counter_enemy_movement == enemy_movement_speed){ // tickrate del movimento dei bullet.
            this->end_game = this->enemy->move_enemy() || this->end_game;
            counter_enemy_movement = -1;
        }
        counter_enemy_movement++;
        counter_enemy_spawn++;
        counter_bullet_movement++;
        counter_fire++;

        this->game_map->print_map(this->p->getY() + this->game_map->get_height() - OFFSET + (OFFSET > this->p->getY() ? OFFSET - this->p->getY() : 0), this->p->get_health(), (this->game_map->get_total_height()-29)/2, this->bullet->get_special_bullet());

        //Spawn e movimento dei bonus
        int height = this->p->getY(); //Prendo la posizione del player
        int should_spawn = (height - 1) % FREQ_SPAWN_BONUS; //In base alla suddetta decido se è il momento di far spawnare un bonus o meno
        
        if(height > 1 && should_spawn == 0 && bonus->get_last_spawn_height() != height){
            this->bonus->add_bonus();
            bonus->set_last_spawn_height(height); //Questo controllo serve per evitare lo spawn di più bonus quando rimango alla stessa altezza per più tempo
        }
        
        if(p->get_exec_bonus() != -1){ 
            this->end_game = this->bonus->exec_bonus(p->get_exec_bonus(), this->p->getX(), this->p->getY()) || this->end_game;
            p->set_exec_bonus(-1);
        }

        //Spawn dei nemici
        if(counter_enemy_spawn == enemy_spawn_speed){
            counter_enemy_spawn = 0;
            Enemy enemy(this->enemy->calculate_spawnpos_x(), this->game_map->get_total_height(), enemy.decide_kind_of_enemy(this->game_map->get_total_height()) );
            this->enemy->add_enemy(enemy);
        }   
    }
}

/*  Author:         Alessandro Frau, Francesco Apollonio (parte dei proiettili speciali)
    Parameters:     void
    Return value:   void
    Comments:       Funzione eseguita da un thread, si occupa di attendere la pressione di un tasto da parte
                    del player, e fa cio che gli viene dato in input dal tasto (spara / fa muovere il player)
*/
void Game::key_listener(void){
    int key;
    while(!this->end_game) {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        this->end_game = this->p->move(key) || this->end_game;
        if(p->get_should_shoot() && !this->end_game){
            p->set_should_shoot(false);
            this->bullet->shoot_bullet();
            //Se sono attivi "bullet speciali", ne scalo uno ad ogni colpo sparato. (Ogni tasto 'spazio' premuto)
            int num_spec_bull = bullet->get_special_bullet();
            if(num_spec_bull > 0){
                bullet->set_special_bullet(--num_spec_bull);
            }
        }
    }
}

/*  Author:         Alessandro Frau
    Parameters:     value -> valore di end_game
    Return value:   void
    Comments:       setta il valore di end_game a value
*/
void Game::set_end_game(bool value){
    this->end_game = value;
}
