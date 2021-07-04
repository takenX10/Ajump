#include "costanti.hpp"
#include "game_printer.h"
#include "Scoreboard.h"
#include "ExternalFunctions.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Bullet.h"
#include "bonus.h"
using namespace std;
using namespace constants;

// TODO: Ogni tanto se colpisci il proiettile di lato si bugga e si blocca il player
// TODO: Se la scoreboard e' vuota si bugga a caso.
// TODO: Commentare megilo la parte bonus.cpp e bonus.h
// TODO: Mettere bonus -> Bonus (maiuscola l'iniziale)
// TODO: Cambiare i nomi alle funzioni e alle variabili seguendo il formato
int main(){
    Scoreboard lboard = Scoreboard("Documents\\leaderboard.txt");
    start_screen(lboard);
    return 0;
}