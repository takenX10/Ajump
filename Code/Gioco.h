#ifndef GIOCO_H
#define GIOCO_H
#include "Mappa.h"
#include "Player.h"
#include "Nemici.h"
#include "Bullet.h"
#include "bonus.h"
void zioporco(void);
class Gioco{
    private:
        Mappa *mappa_gioco;
        Player *p;
        BulletList *proiettili;
        Lista_nemici *nemici;
        Bonus *bonus;
    public:
        Gioco(Mappa *m, Player *p, BulletList *proiettili, Lista_nemici *nemici, Bonus *bon);
        void auto_print_map(void);
        void keyListener(void);
};
#include "Gioco.cpp"
#endif