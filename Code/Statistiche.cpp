#include "Statistiche.h"

// ** Costanti Stats ** //
#define HEART 03
#define EXP "xp"
#define DAMAGE "damage"
#define CHECKPOINT_XP 1000 // punti per ogni superamento di livello
#define SOLDATO_XP 20
#define ARTIGLIERE_XP 10
#define TANK_XP 50
#define BOSS_XP 100

int GetXP_Player(void){
    if (CHECKPOINT == true){
        XP_PLAYER += CHECKPOINT_XP;
    }
    switch (ID_NEMICO){
        case 0: XP_PLAYER;
        case 1: XP_PLAYER += SOLDATO_XP;
        case 2: XP_PLAYER += ARTIGLIERE_XP;
        case 3: XP_PLAYER += TANK_XP;
        case 4: XP_PLAYER += BOSS_XP;
    }
    return XP_PLAYER;
}
/* Stats:
    impaginazione delle Statistiche di Player e Nemici "attivi"
    Idea generale:
    @ Player: 
        XXX ♥
        XXX xp
        XXX dmg
    ----------------
 */
 void Stats(ptr_nodo_nemici nemici){
    // stampa Player
    cout << PLAYER<< "Player:" << endl;
    cout << "\t" << VITA_PLAYER << HEART << endl;
    cout << "\t" << GetXP_Player() << EXP << endl;
    cout << "\t" << DANNO_PLAYER << DAMAGE << endl;
    cout << "----------------"<< endl; // separatore
 }
