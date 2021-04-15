#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Gioco.h"
#include "Alex_constants.hpp"
#include "print_functions.h"
#include "Mappa.h"
#include "Player.h"
#include "../Alessandro.h"

using namespace std;
using namespace constants;

Gioco::Gioco(Mappa *m, Player *p, Lista_proiettili *proiettili, Lista_nemici *nemici){
    this->mappa_gioco = m;
    this->p = p;
    this->proiettili = proiettili;
    this->nemici = nemici;
}
void Gioco::auto_print_map(){
    int counter = 0; // serve per decidere quando far muovere i nemici
    int counter2 = 0;
    int counter3 = 0;
    while(true){
        Sleep(REFRESH_RATE);
        // decidi se far spawnare nemici, e in caso dagli le caratteristiche
        // va implementata la funzione enemy_spawn
        if(counter == 5){ // tickrate del movimento dei proiettili.
            this->proiettili->muovi_proiettili();
            this->nemici->muovi_nemici();
            counter = -1;
        }
        counter++;
        counter2++;
        counter3++;
        
        this->mappa_gioco->printMap(this->p->getY() + this->mappa_gioco->getHeight() - OFFSET + (OFFSET > this->p->getY() ? OFFSET - this->p->getY() : 0) );
        if(this->enemy_spawn() && counter2 == 10){
            counter2 = 0;
            // da creare una funzione per decidere il tipo, per ora settato a 1
            Nemico enemy(this->nemici->calcola_spawnpos_X(), this->mappa_gioco->getTotalHeight(), 1);
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