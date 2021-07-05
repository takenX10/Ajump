
#include "ExternalFunctions.h"
#include "Player.h"
#include "costanti.hpp"
#include "Map.h"
#include <fstream>

using namespace std;
using namespace constants;

/*  Author:         Alex Lorenzato
    Parameters:     mappa, posizione giocatore, punti vita iniziali
    Return value:   none
    Comments:       inizializzazione giocatore
*/
Player::Player(Map *m /*= NULL*/, int x/* = 0*/, int y/* = 1*/, int health_points /* = 100*/){
    this->x = x;
    this->y = y;
    this->ptr_mappa = m;
    this->health_points = health_points;
    this->damage = DANNO_PLAYER;
    if(this->ptr_mappa != NULL){
        this->ptr_mappa->set_char(this->x, this->y , PLAYER);
    }
}

/*  Author:         Alex Lorenzato
    Parameters:     direzione definita dal tasto premuto 
    Return value:   true sse il movimento è permesso
    Comments:       controllo se il movimento è permesso
*/
bool Player::check_movement(int direction){
    switch(direction){
        case SOPRA:
            if(this->ptr_mappa->get_row(this->y + 1)->row[this->x] == PIATTAFORMA){
                return true;
            }
        break;

        case SOTTO:
            if(this->y > 2){
                if(this->ptr_mappa->get_row(this->y - 3)->row[this->x] == PIATTAFORMA){
                    return true;
                }
            }
        break;

        case SINISTRA:
            if(this->x-1 >=0){
                if(this->ptr_mappa->get_row(this->y -1)->row[this->x -1] == PIATTAFORMA){
                    return true;
                }
            }
        break;

        case DESTRA:
            if(this->x+1<this->ptr_mappa->get_width()){
                if(this->ptr_mappa->get_row(this->y -1)->row[this->x +1] == PIATTAFORMA){
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

/*  Author:         Alex Lorenzato (Parte logica), Francesco Apollonio (Parte legata ai bonus)
    Parameters:     direction -> direzione in cui deve avvenire il movimento
    Return value:   restituisce il valore di end_game
    Comments:       Si occupa di muovere il player, cambiargli le cordinate e settare il nuovo carattere nella mappa
*/
bool Player::move(int direction){
    bool end_game = false;
    char oldchar;
    if(this->check_movement(direction) == true){
        switch(direction){
            case SOPRA:
                oldchar = this->ptr_mappa->get_row(this->y+2)->row[this->x];
                if(oldchar == PROIETTILE){
                    // non muoverti perche' e' presente un proiettile nella tua posizione
                    return end_game;
                }
                if(oldchar == CHAR_ARTIGLIERE || oldchar == CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK){
                    end_game = true;
                    return end_game;
                }
                else if(oldchar == BONUS_SALUTE){
                    exec_bonus = COD_BONUS_SALUTE; 
                }
                else if(oldchar == BONUS_BOMBA){
                    exec_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    exec_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    exec_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->set_char(this->x, this->y + 2, PLAYER);
                this->ptr_mappa->set_char(this->x, this->y, SPAZIO_VUOTO);
                this->y += 2;
                // aggiunta new line 
                if(OFFSET < this->y && this->y - OFFSET + this->ptr_mappa->get_height() >  this->ptr_mappa->get_total_height()){
                    this->ptr_mappa->new_row();
                    this->ptr_mappa->new_row();
                }
            break;

            case SOTTO:
                oldchar = this->ptr_mappa->get_row(this->y-2)->row[this->x];
                if(oldchar == CHAR_ARTIGLIERE || oldchar==CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK){
                    end_game = true;
                }
                else if(oldchar == BONUS_SALUTE){
                   exec_bonus = COD_BONUS_SALUTE; //Diamo il valore 1 al bonus salute aggiuntiva
                }
                else if(oldchar == BONUS_BOMBA){
                    exec_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    exec_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    exec_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->set_char(this->x, this->y -2, PLAYER);
                this->ptr_mappa->set_char(this->x, this->y, SPAZIO_VUOTO);
                this->y -= 2;
            break;

            case DESTRA:
                oldchar = this->ptr_mappa->get_row(this->y)->row[this->x + 1];
                if(oldchar == CHAR_ARTIGLIERE || oldchar==CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK){
                    end_game = true;
                }
                else if(oldchar == BONUS_SALUTE){
                    exec_bonus = COD_BONUS_SALUTE; //diamo il valore 1 al bonus salute aggiuntiva
                }
                else if(oldchar == BONUS_BOMBA){
                    exec_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    exec_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    exec_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->set_char(this->x +1, this->y, PLAYER);
                this->ptr_mappa->set_char(this->x, this->y, SPAZIO_VUOTO);
                this->x += 1;
            break;

            case SINISTRA:
                oldchar = this->ptr_mappa->get_row(this->y)->row[this->x - 1];
                if(oldchar == CHAR_ARTIGLIERE || oldchar==CHAR_BOSS || oldchar == CHAR_SOLD_SEMPLICE || oldchar == CHAR_TANK || oldchar == PROIETTILE){
                    end_game = true;
                }
                else if(oldchar == BONUS_SALUTE){
                    exec_bonus = COD_BONUS_SALUTE; //diamo il valore 1 al bonus salute aggiuntiva
                }
                else if(oldchar == BONUS_BOMBA){
                    exec_bonus = COD_BONUS_BOMBA;
                }
                else if(oldchar == MALUS_SALUTE){
                    exec_bonus = COD_MALUS_SALUTE;
                }
                else if(oldchar == BONUS_PROIETTILI_SPECIALI){
                    exec_bonus = COD_BONUS_PROIETTILI_SPECIALI;
                }
                this->ptr_mappa->set_char(this->x -1, this->y, PLAYER);
                this->ptr_mappa->set_char(this->x, this->y, SPAZIO_VUOTO);
                this->x -= 1;
            break;

            case SPAZIO:
                this->should_shoot = true;
            break;
        }
    }
    return end_game;
}


/*  Author:         Alex Lorenzato 
    Parameters:     void
    Return value:   valore della cordinata x del player
    Comments:       restituisce il valore x della cordinata del player
*/
int Player::getX(void){ return this->x; }

/*  Author:         Alex Lorenzato 
    Parameters:     void
    Return value:   valore della cordinata y del player
    Comments:       restituisce il valore y della cordinata del player
*/
int Player::getY(void){ return this->y; }

/*  Author:         Alex Lorenzato 
    Parameters:     void
    Return value:   valore della vita del player
    Comments:       restituisce il valore della vita del player
*/
int Player::get_health(void){ return this->health_points;}

/*  Author:         Alex Lorenzato 
    Parameters:     value -> valore che viene aggiunto alla vita del player (per toglierne passare un valore negativo)
    Return value:   True se il player e' morto, False altrimenti
    Comments:       Cambia la vita del player del valore passato
*/
bool Player::change_health(int value){
    this->health_points = this->health_points + value;
    if (this->health_points <= 0) return true;
    else return false;
}


/*  Author:         Francesco Apollonio
    Parameters:     void
    Return value:   int value -> il danno causato da proietitli "standard" del player
    Comments:       setta il danno del proiettile del player
*/


int Player::get_damage_player(void){
    return this->damage;
}


/*  Author:         Francesco Apollonio
    Parameters:     void
    Return value:   int -> valore che indica se, ed eventualmente quale, bonus è necessario eseguire sul player.
    Comments:       -1 è il valore di default (nessun bonus da eseguire)
*/

int Player::get_exec_bonus(void){
    return this->exec_bonus;
}


/*  Author:         Francesco Apollonio
    Parameters:     int value -> valore da settare per il parametro "exec_bonus".
    Return value:   void
    Comments:       //
*/

void Player::set_exec_bonus(int value){
    this->exec_bonus = value;
}


/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   bool -> valore del parametro "should_shoot"
    Comments:       il valore "should_shoot" permette la comunicazione tra la funzione che fa partire lo sparo e quella che decide se sparare.
*/

bool Player::get_should_shoot(void){
    return this->should_shoot;
}


/*  Author:         Alessandro Frau
    Parameters:     bool value -> parametro che verrà assegnato a "should_shoot"
    Return value:   void
    Comments:       il valore "should_shoot" permette la comunicazione tra la funzione che fa partire lo sparo e quella che decide se sparare.
*/

void Player::set_should_shoot(bool value){
    this->should_shoot = value;
}