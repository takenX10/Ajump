/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
using namespace constants;
using namespace std;

class Nemico{
    public:
        int x;
        int y;
        
};

struct lista_entita{
    Nemico entity;
    bool just_spawned;
    char old_char;
    int move_direction;
    struct lista_entita *next;
    struct lista_entita *prev;

};
typedef lista_entita *ptr_lista_entita;

class gestione_entita{
    protected:
        int list_size;
        ptr_lista_entita head;
    public:
        gestione_entita(void){
            this->head = NULL;
        }
        // aggiunta in testa, quindi se si aggiungono solo nuovi nemici la lista
        // risulta sempre ordinata per le righe
        void aggiungi_nemico(Nemico enemy){
            ptr_lista_entita new_enemy = new lista_entita;
            new_enemy->entity = enemy;
            if (this->head != NULL){
                this->head->prev = new_enemy;
            }
            new_enemy->prev = NULL;
            new_enemy->next = this->head;
            this->head = new_enemy;
        }

        // del player in realta ci interessano solo le coordinate
        // aggiorna il valore della variabile "can_move" di ogni entita della lista
        void nuove_direzioni(Player *player){
            ptr_lista_entita tmp = this->head;
            if(tmp != NULL){
                int playerX = player->getX();
                while(tmp->next != NULL && tmp->next->entity.x < playerX){
                    tmp = tmp->next;
                }
                ptr_lista_entita left = tmp;
                int fdir = 1;
                ptr_lista_entita right;
                ptr_lista_entita first;
                ptr_lista_entita second;
                if (tmp->next == NULL){
                    first = left;
                    second = NULL;
                    right = NULL;
                }else if(playerX == tmp->next->entity.x){
                    right = tmp->next->next;
                }else{
                    right = tmp->next;
                }
                if(right != NULL){
                    if(left->entity.y < right->entity.y){
                        first = left;
                        second = right;
                    }else{
                        first = right;
                        fdir = 0;
                        second = left;
                    }
                }
                while(first != NULL){
                    if((fdir == 1? first->next:first->prev)->entity.x == playerX){
                        first->move_direction = SOTTO;
                    }else{
                        first->move_direction = (fdir == 1? SOTTO_DESTRA: SOTTO_SINISTRA);
                    }
                    first = (fdir == 1? first->next:first->prev);
                }
                while(second != NULL){
                    if((fdir == 0? second->next : second->prev)->entity.x == playerX){
                        second->move_direction = SOTTO;
                    }else{
                        ptr_lista_entita cval = (fdir == 0 ? second->next :second->prev);
                        int movedir = cval->move_direction;
                        if(movedir == SOTTO || (movedir == (fdir == 0 ? SOTTO_DESTRA : SOTTO_SINISTRA) && cval->entity.x == playerX + 1)){
                            second->move_direction = SOTTO;
                        }else{
                            second->move_direction = (fdir == 0? SOTTO_DESTRA : SOTTO_SINISTRA);
                        }
                    }
                    second = (fdir == 0? second->next : second->prev);
                }
                
            }
        }
        
        void muovi_nemici(Mappa *map, Player *player){
            this->nuove_direzioni(player);
            ptr_lista_entita tmp = this->head;
            while(tmp!=NULL){
                if(tmp->just_spawned == true){
                    tmp->old_char = map->getRow(tmp->entity.y)->row[tmp->entity.x];
                    map->setChar(tmp->entity.x, tmp->entity.y, ENEMY_CHAR); // forse qui va cambiato il carattere a seconda del tipo
                    tmp->just_spawned = false;
                }else{
                    map->setChar(tmp->entity.x, tmp->entity.y, tmp->old_char);
                    int newX = tmp->entity.x + (tmp->move_direction == SOTTO_DESTRA?1:0) - (tmp->move_direction == SOTTO_SINISTRA?1:0);
                    int newY = tmp->entity.y + 1; // perche' i nemici vanno sempre e comunque sotto
                    tmp->old_char = map->getRow(newY)->row[newX];
                    map->setChar(newX, newY, ENEMY_CHAR);
                }
            }
        }

        void calcola_spawn(void){
            if(this->list_size != ROW_DIM){
                int numspace = ROW_DIM - this->list_size;
                int spawnpos = rand() % numspace;
                ptr_lista_entita tmp = this->head;
                int n = 0;
                int sum = 0;
                int entityX = spawnpos; // se tmp == NULL allora tutto e' vuoto quindi spawnpos == entityX
                while(n < spawnpos && tmp != NULL){
                    if(tmp->prev == NULL){
                        sum = tmp->entity.x;
                    }else{
                        sum = tmp->entity.x - tmp->prev->entity.x - 1;
                    }
                    if(n+sum >spawnpos){
                        entityX = tmp->entity.x - (n+sum-spawnpos) - 1;
                    }else if(n+sum == spawnpos){
                        entityX = tmp->entity.x - 1;
                    }else if(tmp->next == NULL){
                        entityX = tmp->entity.x + (spawnpos - (n + sum));
                    }
                    n += sum;
                    tmp = tmp->next;
                }
                Nemico enemy = new Nemico(entityX, map->total_height);

            }else{
                // non puo spawnare niente perche' non c'e' spazio
            }
        }
};
