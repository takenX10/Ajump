/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
using namespace std;

class Nemico{
    public:
        int x;
        int y;
        
};

struct lista_entita{
    Nemico entity;
    bool can_move;
    int move_direction;
    struct lista_entita *next;
    struct lista_entita *prev;

};
typedef lista_entita *ptr_lista_entita;

class gestione_entita{
    protected:
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
        void si_puo_muovere(Mappa *map, Player *player){
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
                        first->move_direction = DOWN;
                    }else{
                        first->move_direction = (fdir == 1? DOWN_RIGHT: DOWN_LEFT);
                    }
                }
                
            }
        }
        void muovi_nemici(Mappa *map){

        }
};
