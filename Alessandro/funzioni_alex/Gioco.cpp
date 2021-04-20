#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Gioco.h"
#include "Alex_constants.hpp"
#include "print_functions.h"
#include "Mappa.h"
#include "Player.h"
#include "../Nemici.h"
#include "../Proiettili.h"

using namespace std;
using namespace constants;



Gioco::Gioco(Mappa *m, Player *p, Lista_proiettili *proiettili, Lista_nemici *nemici){
    this->mappa_gioco = m;
    this->p = p;
    this->proiettili = proiettili;
    this->nemici = nemici;
}
void Gioco::auto_print_map(){
    // debug generale, non abbiamo ancora valutato con che criterio
    // far spawnare i nemici quindi usiamo counter1 per il movimento e counter2 per 
    // il tempo che impiegano a nascere
    int counter = 0; // serve per decidere quando far muovere i nemici
    int counter2 = 0;
    int counter_movimento_proiettili = 0;
    int counter_fire = 0;
    // velocita_spawn DEVE essere maggiore di velocita_movimento!!!!!!!!!!!!!!
    // per testare con tante entita 1-3 va bene, piu realistico 4-100
    int velocita_movimento_proiettili = 1;
    int velocita_movimento = velocita_movimento_proiettili * 5; // 1 molto veloce, 20 medio lenta
    int velocita_spawn = velocita_movimento + 50; // 3 molto veloce, 100 medio lenta
    int fire_rate = velocita_movimento_proiettili * 7;
    while(true){
        Sleep(REFRESH_RATE);

        if(counter_movimento_proiettili == velocita_movimento_proiettili){
            this->proiettili->muovi_proiettili();
            counter_movimento_proiettili = -1;
        }

        if(counter_fire == fire_rate){
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
        
        this->mappa_gioco->printMap(this->p->getY() + this->mappa_gioco->getHeight() - OFFSET + (OFFSET > this->p->getY() ? OFFSET - this->p->getY() : 0) );
        
        // decidi se far spawnare nemici, e in caso dagli le caratteristiche
        // va implementata la funzione enemy_spawn
        if(this->enemy_spawn() && counter2 == velocita_spawn){
            counter2 = 0;
            // da creare una funzione per decidere il tipo, per ora settato a 1
            Nemico enemy(this->nemici->calcola_spawnpos_X(), this->mappa_gioco->getTotalHeight());
            enemy.decide_kindOfEnemy(this->mappa_gioco->getHeight());
            this->nemici->aggiungi_nemico(enemy);
        }
    }
}
void Gioco::keyListener(){
    int key;
    while(true) {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        this->p->move(key);
    }
}

// funzione che decide se far spawnare un nemico o no
bool Gioco::enemy_spawn(void){
    return true;
}