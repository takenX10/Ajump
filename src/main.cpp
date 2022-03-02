#include "costanti.hpp"
#include "game_printer.h"
#include "Scoreboard.h"
#include "ExternalFunctions.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Bullet.h"
#include "Bonus.h"
using namespace std;
using namespace constants;

int main(){
    Scoreboard lboard = Scoreboard("Documents\\leaderboard.txt");
    start_screen(lboard);
    return 0;
}