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
    constexpr int REFRESH_RATE = 1;     // durata della sleep tra un print e l'altro
    constexpr int CHECKPOINT_ROW = 50;   // frequenza con cui si trova il piano con piattaforma a larghezza ROW_DIM

    // Caratteri
    constexpr char MURO =  177;
    constexpr char PIATTAFORMA = 196;
    constexpr char ENEMY_CHAR = 'V';
    constexpr char PROIETTILE = '+';
    constexpr char PLAYER = '@';

    // Direzioni
    constexpr int SOPRA = 72;
    constexpr int SOTTO = 80;
    constexpr int DESTRA = 77;
    constexpr int SINISTRA = 75;
    constexpr int SPAZIO = 32;
    constexpr int SOTTO_DESTRA = -1; // questo valore non e' influente, basta che sia diverso da tutte le altre direzioni
    constexpr int SOTTO_SINISTRA = -2; // stessa cosa scritta sopra

    // Giocatore
    constexpr int STARTING_X = ROW_DIM/2;
    constexpr int STARTING_Y = 1;
    constexpr int OFFSET = 6;
}
using namespace constants;
#endif