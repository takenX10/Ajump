#ifndef ALEX_CONSTANTS_HPP
#define ALEX_CONSTANTS_HPP
/*
per usare costanti:
#include "path_to_this_file"
using namespace constants;
*/
namespace constants{
    // Costanti mappa
    constexpr int ROW_DIM = 40;
    constexpr int MAP_HEIGHT = 30;
    constexpr int REFRESH_RATE = 30;     // durata della sleep tra un print e l'altro
    constexpr int CHECKPOINT_ROW = 50;   // frequenza con cui si trova il piano con piattaforma a larghezza ROW_DIM

    // Caratteri
    constexpr char MURO =  147;
    constexpr char PIATTAFORMA = 196;

    // Direzioni
    constexpr int SOPRA = 72;
    constexpr int SOTTO = 80;
    constexpr int DESTRA = 77;
    constexpr int SINISTRA = 75;
    constexpr int SPAZIO = 32;

}
#endif