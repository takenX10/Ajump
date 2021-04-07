#include <iostream>
#include<chrono>
#include<thread>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "funzioni_alex/Gioco.h"
#include "funzioni_alex/print_functions.h"

using namespace std;
using namespace constants;

int main(void){

    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    Gioco  g = Gioco(&m, &p);

    hidecursor();                         // per rendere il cursore invisibile

    thread print_map_thread(&Gioco::auto_print_map, g);
    thread get_position(&Gioco::keyListener, g);

    print_map_thread.join();
    get_position.join();
}