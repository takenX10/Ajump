
#ifndef PLAYER_H
#define PLAYER_H

#include "Mappa.h"
class Player{
    private:
        int x;
        int y;
        int health_points;
        Mappa *ptr_mappa;
    public:
        int damage; //Danno del Player
        int esegui_bonus = -1; //Con questo paramentro comunico alla classe Bonus se ed eventualmente quale bonus eseguire nel momento in cui player ci passa sopra; -1 è default.
        bool deve_sparare = false;
        Player(Mappa *m = NULL, int x = 0, int y = 1, int health_points = VITA_PLAYER);
        bool checkMovement(int direction);
        void move(int direction);
        int getX(void);
        int getY(void);
        int get_health(void);
        //Modifica salute del player; restituisce True se player è morto.
        bool change_health(int value);
};
#include "Player.cpp"
#endif