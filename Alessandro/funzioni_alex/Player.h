
#ifndef PLAYER_H
#define PLAYER_H

#include "Mappa.h"
class Player{
    private:
        int x;
        int y;
        Mappa *ptr_mappa;

    public:
        bool deve_sparare = false;
        Player(Mappa *m = NULL, int x = 0, int y = 1);
        bool checkMovement(int direction);
        void move(int direction);
        int getX(void);
        int getY(void);
};
#include "Player.cpp"
#endif