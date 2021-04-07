#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Gioco.h"
#include "Alex_constants.hpp"
#include "print_functions.h"
#include "Mappa.h"
#include "Player.h"

using namespace std;
using namespace constants;

Gioco::Gioco(Mappa *m, Player *p){
    this->mappa_gioco = m;
    this->p = p;
}
void Gioco::auto_print_map(){
    while(true){
        Sleep(REFRESH_RATE);
        this->mappa_gioco->printMap(this->p->getY() + this->mappa_gioco->getHeight() - OFFSET + (OFFSET > this->p->getY() ? OFFSET - this->p->getY() : 0) );
    }
}
void Gioco::keyListener(){
    int key;
    while(true) {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        this->p->move(key);
    }
}
