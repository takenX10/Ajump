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
#include <time.h>

using namespace std;
using namespace constants;

void endfunction(void){
    cout<<"partita finita";
}

int main(void){
    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    Lista_proiettili proiettili = Lista_proiettili(&m, &p);
    Lista_nemici ent = Lista_nemici(&m, &p, &proiettili);
    Bonus bonus = Bonus(&m, &p, &ent, &proiettili);
    Gioco  g = Gioco(&m, &p, &proiettili, &ent, &bonus);

 
    hidecursor(); // per rendere il cursore invisibile

    thread print_map_thread(&Gioco::auto_print_map, g);
    thread get_position(&Gioco::keyListener, g);

    print_map_thread.join();
    get_position.join();
}