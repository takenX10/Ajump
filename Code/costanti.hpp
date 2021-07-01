#ifndef costanti_HPP
#define costanti_HPP
/*
per usare costanti:
#include "path_to_this_file"
using namespace constants;
*/
bool end_game = false; // TODO: ATTENTO A STA VARIABILE GLOBALE
namespace constants{

    /* Costanti mappa */
    constexpr int ROW_DIM = 40;
    constexpr int MAP_HEIGHT = 30;
    constexpr int REFRESH_RATE = 1;     // durata della sleep tra un print e l'altro
    constexpr int CHECKPOINT_ROW = 50;   // frequenza con cui si trova il piano con piattaforma a larghezza ROW_DIM


    /* Caratteri e Codici */

        //Caratteri mappa
        constexpr char SPAZIO_VUOTO = ' ';
        constexpr char MURO =  177;
        constexpr char PIATTAFORMA = 196;
        
        //Caratteri personaggi e proiettile
        constexpr char PLAYER = '@';
        constexpr char DESTRUCT_PLAYER = '#';
        constexpr char CHAR_ARTIGLIERE = 'A';
        constexpr char CHAR_SOLD_SEMPLICE = 'S';
        constexpr char CHAR_TANK = 'T';
        constexpr char CHAR_BOSS = 'B';
        constexpr char PROIETTILE = '+';

        //Caratteri Bonus
        constexpr char BONUS_SALUTE = 'H'; //Il bonus incrementa la salute del player  
        constexpr char MALUS_SALUTE = 'M'; //Il malus diminuisce la salute del player
        constexpr char BONUS_BOMBA = 'O'; //Il bonus distrugge tutti i nemici presenti nella mappa
        constexpr char BONUS_PROIETTILI_SPECIALI = 'P'; //Il bonus da al player tot proiettili MOLTO più potenti

        //Codici Nemici & Bonus (Non modificare)
        constexpr int  COD_SOLD_SEMPLICE = 1;
        constexpr int  COD_ARTIGLIERE = 2;
        constexpr int  COD_TANK = 3;
        constexpr int  COD_BOSS = 4;
        constexpr int  COD_BONUS_SALUTE = 1;
        constexpr int  COD_BONUS_BOMBA = 2;
        constexpr int  COD_MALUS_SALUTE = 3;
        constexpr int  COD_BONUS_PROIETTILI_SPECIALI = 4;
        constexpr int  BONUS_TOTALI = 4; //Numero di bonus esistenti

    /* Direzioni */

        constexpr int SOPRA = 72;
        constexpr int SOTTO = 80;
        constexpr int DESTRA = 77;
        constexpr int SINISTRA = 75;
        constexpr int SPAZIO = 32;
        constexpr int SOTTO_DESTRA = -1; // questo valore non e' influente, basta che sia diverso da tutte le altre direzioni
        constexpr int SOTTO_SINISTRA = -2; // stessa cosa scritta sopra

    
    /* Parametri di gioco */

    // Difficoltà
    constexpr int STEP_DIFFICOLTA = 50; // Stabilisce ogni quante righe viene aumentato il livello di difficoltà
    constexpr int FREQ_SPAWN_BONUS = 50; // Stabilisce la frequenza con cui spawnano i Bonus ( ogni 50 righe ) 
    constexpr int DIFFICOLTA_ESTREMA = 1000; //Stabilisce la riga oltre la quale spawnano solo BOSS: la difficoltà diventa estrema.

    // Bonus
    constexpr int VALORE_BONUS_SALUTE = 100;
    constexpr int VALORE_MALUS_SALUTE = -200;
    constexpr int NUMERO_PROIETTILI_SPECIALI = 20;
    constexpr int DANNO_PROIETT_SPECIALE = 300; //Con questo danno one shotto chiunque

    // Player
    constexpr int DANNO_PLAYER = 50;
    constexpr int VITA_PLAYER = 200;

    // Spawn del player
    constexpr int STARTING_X = ROW_DIM/2;
    constexpr int STARTING_Y = 1;
    constexpr int OFFSET = 6;


    // Nemici
    constexpr int VITA_SOLD_SEMPLICE = 100;
    constexpr int DANNO_SOLD_SEMPLICE = 10;
    constexpr int VITA_ARTIGLIERE = 50;
    constexpr int DANNO_ARTIGLIERE = 20;
    constexpr int VITA_TANK = 150;
    constexpr int DANNO_TANK = 5;
    constexpr int VITA_BOSS = 300;
    constexpr int DANNO_BOSS = 50;

    /* Punteggio */
        bool CHECKPOINT = false;
        int ID_NEMICO = 0;
        int XP_PLAYER;
}
using namespace constants;
#endif