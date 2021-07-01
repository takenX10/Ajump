#ifndef STATISTICHE_H
#define STATISTICHE_H

#include <iostream>
#include <windows.h>
#include "Mappa.h" 
#include "Player.h"
#include "costanti.hpp"
#include "Gioco.h" 
#include "print_functions.h"
#include "bonus.h"
#include "Nemici.h"
#include "Proiettili.h"

using namespace std;

 /*  Calcola punteggio del Player:
    - in base al checkpoint
    - ad ogni morte di un nemico
 */
int GetXP_Player(); //


/*  Stats:
    impaginazione delle Statistiche di Player e Nemici "attivi"
 */
 void Stats(ptr_nodo_nemici nemici);

#include "Statistiche.cpp"
#endif