#include <iostream>
#include <windows.h>
#include <conio.h>
#include "ExternalFunctions.h"
#include "costanti.hpp"
#include "Gioco.h"
#include "Mappa.h"
#include "Player.h"
#include "Nemici.h"
#include "Bullet.h"
#include "bonus.h"
#include "alice.h"
//#include "../Alice/alice.cpp"

using namespace std;
using namespace constants;

Gioco::Gioco(Mappa *m, Player *p, BulletList *proiettili, Lista_nemici *nemici, Bonus *bon){
    this->mappa_gioco = m;
    this->p = p;
    this->proiettili = proiettili;
    this->nemici = nemici;
    this->bonus = bon;
}
void Gioco::auto_print_map(){

    int counter = 0; // serve per decidere quando far muovere i nemici
    int counter2 = 0; // tempo che impiegano i nemici a nascere
    int counter_movimento_proiettili = 0;
    int counter_fire = 0;
    int velocita_movimento_proiettili = 1;
    int velocita_movimento = velocita_movimento_proiettili * 10;
    //I due parametri seguenti possono essere modificati per aumentare la difficoltà del gioco gradualmente
    int velocita_spawn_nemici = velocita_movimento + 100;
    int fire_rate_nemici = velocita_movimento_proiettili * 30;
    int difficolta = STEP_DIFFICOLTA; //Questo variabile stabilisce ogni quante righe viene aumentato il livello di difficoltà
    while(!end_game){       

        //Il seguente IF permette l'aumento graduale della difficoltà, andando a modificare
        //la velocità di spawn dei nemici, e quindi il numero di nem da affrontare contemporaneamente.
        if(this->p->getY() > 1){
            if((this->p->getY() - 1) % difficolta == 0 && velocita_spawn_nemici - 10 > velocita_movimento){
            counter2 = 0;
            velocita_spawn_nemici = (velocita_spawn_nemici - 10);
            difficolta += STEP_DIFFICOLTA;
            }
        }
        Sleep(REFRESH_RATE);
        
        if(counter_movimento_proiettili == velocita_movimento_proiettili){
            this->proiettili->move_bullet();
            if(this->proiettili->get_damage_enemy_x() != -1){
                this->nemici->danneggia_nemico_x(this->proiettili->get_damage_enemy_x());
                this->proiettili->set_damage_enemy_x(-1);
            }
            counter_movimento_proiettili = -1;
        }

        if(counter_fire == fire_rate_nemici){
            this->nemici->spara();
            counter_fire = -1;
        }

        if(counter == velocita_movimento){ // tickrate del movimento dei proiettili.
            this->nemici->muovi_nemici();
            counter = -1;
        }
        counter++;
        counter2++;
        counter_movimento_proiettili++;
        counter_fire++;

        this->mappa_gioco->printMap(this->p->getY() + this->mappa_gioco->getHeight() - OFFSET + (OFFSET > this->p->getY() ? OFFSET - this->p->getY() : 0), this->p->get_health(), (this->mappa_gioco->getTotalHeight()-29)/2, this->proiettili->get_special_bullet());

        //Spawn e movimento dei bonus
        int altezza = this->p->getY(); //Prendo la posizione del player
        int deve_spawnare = (altezza - 1) % FREQ_SPAWN_BONUS; //In base alla suddetta decido se è il momento di far spawnare un bonus o meno
        
        if(altezza > 1 && deve_spawnare == 0 && bonus->get_last_spawn_height() != altezza){
            this->bonus->aggiungi_bonus();
            bonus->set_last_spawn_height(altezza); //Questo controllo serve per evitare lo spawn di più bonus quando rimango alla stessa altezza per più tempo
        }
        
        if(this->p->esegui_bonus != -1){ 
            this->bonus->esegui_bonus(this->p->esegui_bonus, this->p->getX(), this->p->getY());
            this->p->esegui_bonus = -1;
        }

        //Spawn dei nemici
        if(counter2 == velocita_spawn_nemici){
            counter2 = 0;
            Nemico enemy(this->nemici->calcola_spawnpos_X(), this->mappa_gioco->getTotalHeight(), enemy.decide_kindOfEnemy(this->mappa_gioco->getTotalHeight()) );
            this->nemici->aggiungi_nemico(enemy);
        }   
    }
}


void Gioco::keyListener(void){
    int key;
    while(!end_game) {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        this->p->move(key);
        if(this->p->deve_sparare && !end_game){
            this->p->deve_sparare = false;
            this->proiettili->shoot_bullet();
            //Se sono attivi "proiettili speciali", ne scalo uno ad ogni colpo sparato. (Ogni tasto 'spazio' premuto)
            int num_spec_bull = proiettili->get_special_bullet();
            if(num_spec_bull > 0){
                proiettili->set_special_bullet(--num_spec_bull);
            }
        }
    }
}

