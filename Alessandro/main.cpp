#include <iostream>
#include <chrono>
#include <thread>
#include "funzioni_alex/Mappa.h" 
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "funzioni_alex/Gioco.h" 
#include "funzioni_alex/print_functions.h"
#include "bonus.h"
#include "Nemici.h"
#include "Proiettili.h"
#include "../Alice/Statistiche.h"
#include "../Alice/alice.cpp"
#include <time.h>

using namespace std;
using namespace constants;


int main(void){
    
    // la patch del file va modificata in base a dove si runna 
    Classifica lboard = Classifica("C:\\Users\\theas\\Documents\\GitHub\\Ajump\\Alice\\leaderboard.txt");
    StartScreen(lboard);
    return 0;
}