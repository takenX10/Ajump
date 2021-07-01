
#include "Player.h"
#include "print_functions.h"
#include "costanti.hpp"
#include "Mappa.h"
#include <fstream>

using namespace std;
using namespace constants;

Player::Player(Mappa *m /*= NULL*/, int x/* = 0*/, int y/* = 1*/, int health_points /* = 100*/){
    this->x = x;
    this->y = y;
    this->ptr_mappa = m;
    this->health_points = health_points;
    this->damage = DANNO_PLAYER;
    if(this->ptr_mappa != NULL){
        this->ptr_mappa->setChar(this->x, this->y , PLAYER);
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
                if(oldchar == PROIETTILE){
                    // non muoverti perche' e' presente un proiettile nella tua posizione
                    return;
                }
                if(oldchar == CHAR_ARTIGLIERE || oldchar == CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK){
                    end_game = true;
                    return;
                }
                else if(oldchar == BONUS_SALUTE){
                    esegui_bonus = COD_BONUS_SALUTE; 
                }
                else if(oldchar == BONUS_BOMBA){
                    esegui_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    esegui_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    esegui_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->setChar(this->x, this->y + 2, PLAYER);
                this->ptr_mappa->setChar(this->x, this->y, SPAZIO_VUOTO);
                this->y += 2;
                // aggiunta new line 
                if(OFFSET < this->y && this->y - OFFSET + this->ptr_mappa->getHeight() >  this->ptr_mappa->getTotalHeight()){
                    this->ptr_mappa->newRow();
                    this->ptr_mappa->newRow();
                }
            break;

            case SOTTO:
                oldchar = this->ptr_mappa->getRow(this->y-2)->row[this->x];
                if(oldchar == CHAR_ARTIGLIERE || oldchar==CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                else if(oldchar == BONUS_SALUTE){
                   esegui_bonus = COD_BONUS_SALUTE; //Diamo il valore 1 al bonus salute aggiuntiva
                }
                else if(oldchar == BONUS_BOMBA){
                    esegui_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    esegui_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    esegui_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->setChar(this->x, this->y -2, PLAYER);
                this->ptr_mappa->setChar(this->x, this->y, SPAZIO_VUOTO);
                this->y -= 2;
            break;

            case DESTRA:
                oldchar = this->ptr_mappa->getRow(this->y)->row[this->x + 1];
                if(oldchar == CHAR_ARTIGLIERE || oldchar==CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                else if(oldchar == BONUS_SALUTE){
                    esegui_bonus = COD_BONUS_SALUTE; //diamo il valore 1 al bonus salute aggiuntiva
                }
                else if(oldchar == BONUS_BOMBA){
                    esegui_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    esegui_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    esegui_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->setChar(this->x +1, this->y, PLAYER);
                this->ptr_mappa->setChar(this->x, this->y, SPAZIO_VUOTO);
                this->x += 1;
            break;

            case SINISTRA:
                oldchar = this->ptr_mappa->getRow(this->y)->row[this->x - 1];
                if(oldchar == CHAR_ARTIGLIERE || oldchar==CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                else if(oldchar == BONUS_SALUTE){
                    esegui_bonus = COD_BONUS_SALUTE; //diamo il valore 1 al bonus salute aggiuntiva
                }
                else if(oldchar == BONUS_BOMBA){
                    esegui_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    esegui_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    esegui_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->setChar(this->x -1, this->y, PLAYER);
                this->ptr_mappa->setChar(this->x, this->y, SPAZIO_VUOTO);
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

//Modifica la vita del player. Restituisce True se il player è morto
bool Player::change_health(int value){

    //For debug purpose
    ofstream stats;
    stats.open("statsPlayer.txt");
    stats << "Vita -> " << this->health_points << "\nDanno / Bonus / Malus che sto per subire -> " << value << endl;
    //end of debug test

    this->health_points = this->health_points + value;
    
    //Debug
    stats << "Vita dopo l'ultima modifica -> " << health_points;
    stats.close();
    //Ancora debug
    if (this->health_points <= 0) return true;
    else return false;
}

