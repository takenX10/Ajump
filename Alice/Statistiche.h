#ifndef STATISTICHE_H
#define STATISTICHE_H

#include <iostream>
#include <windows.h>
#include "../Alessandro/funzioni_alex/Mappa.h" 
#include "../Alessandro/funzioni_alex/Player.h"
#include "../Alessandro/funzioni_alex/Alex_constants.hpp"
#include "../Alessandro/funzioni_alex/Gioco.h" 
#include "../Alessandro/funzioni_alex/print_functions.h"
#include "../Alessandro/bonus.h"
#include "../Alessandro/Nemici.h"
#include "../Alessandro/Proiettili.h"

using namespace std;

 /*  Calcola punteggio del Player:
    - in base al checkpoint
    - ad ogni morte di un nemico
 */
int GetXP_Player(); //

/*  Stats Enemy:
    - vita
    - danni
 */
void Stats_Enemy(ptr_nodo_nemici nemici);

/*  Stats:
    impaginazione delle Statistiche di Player e Nemici "attivi"
 */
 void Stats(ptr_nodo_nemici nemici);

#include "Statistiche.cpp"
#endif