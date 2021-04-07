
#include "Player.h"
#include "print_functions.h"
#include "Alex_constants.hpp"
#include "Mappa.h"

using namespace std;
using namespace constants;

Player::Player(Mappa *m /*= NULL*/, int x/* = 0*/, int y/* = 1*/){
    this->x = x;
    this->y = y;
    this->ptr_mappa = m;
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

        break;
    }
    return false;
}

void Player::move(int direction){
    if(this->checkMovement(direction) == true){
        switch(direction){
            case SOPRA:
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
                this->ptr_mappa->setChar(this->x, this->y -2, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->y -= 2;
            break;

            case DESTRA:
                this->ptr_mappa->setChar(this->x +1, this->y, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->x += 1;
            break;

            case SINISTRA:
                this->ptr_mappa->setChar(this->x -1, this->y, '@');
                this->ptr_mappa->setChar(this->x, this->y, ' ');
                this->x -= 1;
            break;

            case SPAZIO:

            break;
        }
    }
}

int Player::getX(void){ return this->x; }
int Player::getY(void){ return this->y; }
