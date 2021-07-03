#ifndef STATISTICHE_H
#define STATISTICHE_H

#include <iostream>
#include <windows.h>
#include "ExternalFunctions.h"
#include "costanti.hpp"
#include "Mappa.h" 
#include "Player.h"
#include "Gioco.h" 
#include "bonus.h"
#include "Nemici.h"
#include "Bullet.h"

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