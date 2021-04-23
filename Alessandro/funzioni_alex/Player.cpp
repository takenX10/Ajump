
#include "Player.h"
#include "print_functions.h"
#include "Alex_constants.hpp"
#include "Mappa.h"
#include <fstream>

using namespace std;
using namespace constants;

Player::Player(Mappa *m /*= NULL*/, int x/* = 0*/, int y/* = 1*/, int health_points /* = 100*/, int damage /* = 10 */){
    this->x = x;
    this->y = y;
    this->ptr_mappa = m;
    this->health_points = health_points;
    this->damage = damage;
    if(this->ptr_mappa != NULL){
        this->ptr_mappa->setChar(this->x, this->y , '@');
    }
}

bool Player::checkMovement(int direction){
    switch(direction){
        case SOPRA:
            if(this->ptr_mappa->getRow(this->y + 1)->row[this->x] == PIATTAFORMA){
                return true;
            }
        break;

        case SOTTO:
            if(this->y > 2){
                if(this->ptr_mappa->getRow(this->y - 3)->row[this->x] == PIATTAFORMA){
                    return true;
                }
            }
            
        break;

        case SINISTRA:
            if(this->x-1 >=0){
                if(this->ptr_mappa->getRow(this->y -1)->row[this->x -1] == PIATTAFORMA){
                    return true;
                }
            }
        break;

        case DESTRA:
            if(this->x+1<this->ptr_mappa->getWidth()){
                if(this->ptr_mappa->getRow(this->y -1)->row[this->x +1] == PIATTAFORMA){
                    return true;
                }
            }
        break;

        case SPAZIO:
            return true;
        break;
    }
    return false;
}

void Player::move(int direction){
    char oldchar;
    if(this->checkMovement(direction) == true){
        switch(direction){
            case SOPRA:
                oldchar = this->ptr_mappa->getRow(this->y+2)->row[this->x];
                if(oldchar == ENEMY_CHAR_ARTIGLIERE || oldchar == ENEMY_CHAR_BOSS || oldchar == ENEMY_CHAR_SOLD_SEMPLICE || oldchar == ENEMY_CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                this->ptr_mappa->setChar(this->x, this->y +2, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->y += 2;
                // aggiunta new line 
                if(OFFSET < this->y && this->y - OFFSET + this->ptr_mappa->getHeight() >  this->ptr_mappa->getTotalHeight()){
                    this->ptr_mappa->newRow();
                    this->ptr_mappa->newRow();
                }
            break;

            case SOTTO:
                oldchar = this->ptr_mappa->getRow(this->y-2)->row[this->x];
                if(oldchar == ENEMY_CHAR_ARTIGLIERE || oldchar==ENEMY_CHAR_BOSS || oldchar == ENEMY_CHAR_SOLD_SEMPLICE || oldchar == ENEMY_CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                this->ptr_mappa->setChar(this->x, this->y -2, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->y -= 2;
            break;

            case DESTRA:
                oldchar = this->ptr_mappa->getRow(this->y)->row[this->x + 1];
                if(oldchar == ENEMY_CHAR_ARTIGLIERE || oldchar==ENEMY_CHAR_BOSS || oldchar == ENEMY_CHAR_SOLD_SEMPLICE || oldchar == ENEMY_CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                this->ptr_mappa->setChar(this->x +1, this->y, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->x += 1;
            break;

            case SINISTRA:
                oldchar = this->ptr_mappa->getRow(this->y)->row[this->x - 1];
                if(oldchar == ENEMY_CHAR_ARTIGLIERE || oldchar==ENEMY_CHAR_BOSS || oldchar == ENEMY_CHAR_SOLD_SEMPLICE || oldchar == ENEMY_CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                this->ptr_mappa->setChar(this->x -1, this->y, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->x -= 1;
            break;

            case SPAZIO:
                this->deve_sparare = true;
            break;
        }
    }
}

int Player::getX(void){ return this->x; }
int Player::getY(void){ return this->y; }

bool Player::is_dead(int value){
    ofstream stats;
    stats.open("statsPlayer.txt");
    stats << "Vita -> " << this->health_points << "\n Danno che sto per subire -> " << value << endl;
    this->health_points = this->health_points - value;
    stats << health_points;
    stats.close();
    if (this->health_points <= 0) return true;
    else return false;
}
