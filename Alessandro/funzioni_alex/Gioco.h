#ifndef GIOCO_H
#define GIOCO_H
#include "Mappa.h"
#include "Player.h"
class Gioco{
    private:
        Mappa *mappa_gioco;
        Player *p;

    public:
        Gioco(Mappa *m, Player *p);
        void auto_print_map(void);
        void keyListener(void);
};
#include "Gioco.cpp"
#endif