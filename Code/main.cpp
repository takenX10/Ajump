#include <iostream>
#include <chrono>
#include <thread>
#include "Mappa.h" 
#include "Player.h"
#include "costanti.hpp"
#include "Gioco.h" 
#include "print_functions.h"
#include "bonus.h"
#include "Nemici.h"
#include "Proiettili.h"
#include "Statistiche.h"
#include "alice.h"
#include <time.h>

using namespace std;
using namespace constants;
// TODO: se hai tempo fixa bug trattini che rimangono in giro 
void endfunction(){
    cout<<"partita finita";
 //   GameOver((m.getTotalHeight()-29)/2);
}

int main(void){
    
    // la patch del file va modificata in base a dove si runna 
    Classifica lboard = Classifica("Documents\\leaderboard.txt");
    StartScreen(lboard);
    return 0;
}