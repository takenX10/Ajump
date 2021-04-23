
#ifndef PLAYER_H
#define PLAYER_H

#include "Mappa.h"
class Player{
    private:
        int x;
        int y;
        int health_points;
        int damage;
        Mappa *ptr_mappa;

    public:
        bool deve_sparare = false;
        Player(Mappa *m = NULL, int x = 0, int y = 1, int health_points = 100, int damage = 10);
        bool checkMovement(int direction);
        void move(int direction);
        int getX(void);
        int getY(void);
        //Il seguente metodo sottrae value alla salute
        //del player e ti dice se è morto o no
        bool is_dead(int value);
};
#include "Player.cpp"
#endif