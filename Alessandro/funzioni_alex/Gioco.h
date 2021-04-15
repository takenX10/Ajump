#ifndef GIOCO_H
#define GIOCO_H
#include "Mappa.h"
#include "Player.h"
#include "../Alessandro.h"
class Gioco{
    private:
        Mappa *mappa_gioco;
        Player *p;
        Lista_proiettili *proiettili;
        Lista_nemici *nemici;

    public:
        Gioco(Mappa *m, Player *p, Lista_proiettili *proiettili, Lista_nemici *nemici);
        void auto_print_map(void);
        void keyListener(void);
        bool enemy_spawn(void);
};
#include "Gioco.cpp"
#endif