/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<string>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "Alessandro.h"
using namespace constants;
using namespace std;

#include <fstream>
///// debug
string where(int n){
    switch(n){
        case SOTTO:
            return "SOTTO         ";
            break;
        case SOTTO_DESTRA:
            return "SOTTO_DESTRA  ";
        case SOTTO_SINISTRA:
            return "SOTTO_SINISTRA";
        default:
            return "NON_LO_SO     ";
    }
    return "NON_LO_SO     ";
}

void printfile(ptr_nodo_nemici lista){
  ofstream myfile;
  myfile.open ("lista.txt");
  int i = 0;
  while(lista!=NULL){
      myfile << to_string(i) << ") "<<(i>9?"":" ")<<"Movedir:"<<where(lista->move_direction)<<" X:"<<to_string(lista->entity.x)<<(lista->entity.x>9?"":" ")<<" Y:"<<to_string(lista->entity.y)<<(lista->entity.y>9?"":" ")<<endl;
      i++;
      lista = lista->next;
  }
  myfile.close();
}
/////

Nemico::Nemico(int x, int y, int tipo){
    this->x = x;
    this->y = y;
    this->tipo = tipo;
}

Lista_nemici::Lista_nemici(Mappa *map, Player *p){
    this->head = NULL;
    this->map = map;
    this->player = p;
    this->list_size = 0;
    this->current_id = 0;
}

// aggiunta mantenendo ordine per colonne
// si da per scontato che non sia presente nessun altro nemico
// nella colonna in cui e' situato enemy
// per decidere la coordinata x di enemy e' opportuno usare la funzione
// get_spawnpos_X di questa classe
void Lista_nemici::aggiungi_nemico(Nemico enemy){
    this->list_size++;
    ptr_nodo_nemici new_enemy = new nodo_nemici;
    new_enemy->entity = enemy;
    new_enemy->id = this->current_id;
    this->current_id++;
    if (this->head == NULL){
        this->head = new_enemy;
        new_enemy->next = new_enemy->prev = NULL;
    }else{
        ptr_nodo_nemici tmp = this->head;
        while(tmp->next != NULL && tmp->entity.x < new_enemy->entity.x){
            tmp = tmp->next;
        }
        if(tmp->entity.x > new_enemy->entity.x){
            if(tmp->prev == NULL){
                this->head = new_enemy;
                new_enemy->prev = NULL;
                new_enemy->next = tmp;
                tmp->prev = new_enemy;
            }else{
                tmp->prev->next = new_enemy;
                new_enemy->prev = tmp->prev;
                new_enemy->next = tmp;
                tmp->prev = new_enemy;
            }
        }else{
            tmp->next = new_enemy;
            new_enemy->prev = tmp;
            new_enemy->next = NULL;
        }
    }
    printfile(this->head);
}

// del player in realta ci interessano solo le coordinate
// aggiorna il valore della variabile "can_move" di ogni entita della lista
void Lista_nemici::nuove_direzioni(void){
    ptr_nodo_nemici tmp = this->head;
    if(tmp != NULL){
        int playerX = player->getX();
        while(tmp->next != NULL && tmp->next->entity.x < playerX){
            tmp = tmp->next;
        }
        ptr_nodo_nemici left = tmp;
        int fdir;
        ptr_nodo_nemici right;
        ptr_nodo_nemici first;
        ptr_nodo_nemici second;
        if(tmp->next == NULL && tmp->entity.x <= playerX){
            left = tmp;
            right = NULL;
        }else if(tmp->prev == NULL && tmp->entity.x > playerX){
            left = NULL;
            right = tmp;
        }else{
            left = tmp;
            right = tmp->next;
        }
        if(right == NULL){
            first = left;
            second = NULL;
            fdir = 1;
        }else if(left == NULL){
            first = right;
            second = NULL;
            fdir = 0;
        }else if(left->entity.y > right->entity.y){
            first = right;
            second = left;
            fdir = 0;
        }else{
            first = left;
            second = right;
            fdir = 1;
        }
        while(first != NULL){
            ptr_nodo_nemici next_node = (fdir == 1 ? first->next : first->prev);
            if(first->entity.x == playerX){
                first->move_direction = SOTTO;
            }else{
                int newdir = (fdir == 1 ? SOTTO_DESTRA : SOTTO_SINISTRA);
                if(next_node == NULL){
                    first->move_direction = newdir;
                }else if(first->just_spawned == true){
                    first->move_direction = SOTTO;
                }else if(next_node->entity.x == first->entity.x + (fdir == 1 ? 1 : -1)){
                    if(next_node->entity.x == playerX){
                        first->move_direction = SOTTO;
                    }else if(next_node->move_direction == SOTTO){
                        first->move_direction = SOTTO;
                    }else{
                        first->move_direction = newdir;
                    }
                }else{
                    first->move_direction = newdir;
                }
            } 
            first = (fdir == 1 ? first->prev : first->next);
        }
        while(second != NULL){
            ptr_nodo_nemici next_node = (fdir == 1 ? second->prev : second->next);
            int newdir = (fdir == 1 ? SOTTO_SINISTRA : SOTTO_DESTRA);
            if(second->entity.x == playerX){
                second->move_direction = SOTTO;
            }else if(second->just_spawned == true){
                second->move_direction = SOTTO;
            }else if(next_node != NULL){
                if(next_node->entity.x == second->entity.x + (fdir == 1 ? -2 : 2)){
                    if(next_node->move_direction == SOTTO || next_node->move_direction == newdir){
                        second->move_direction = newdir;
                    }else{
                        second->move_direction = SOTTO;
                    }
                }else if(next_node->entity.x == second->entity.x + (fdir == 1 ? -1 : 1)){
                    if(next_node->move_direction == newdir){
                        second->move_direction = newdir;
                    }else{
                        second->move_direction = SOTTO;
                    }
                }else{
                    second->move_direction = newdir;
                }
            }else{
                second->move_direction = newdir;
            }
            second = (fdir == 1 ? second->next : second->prev);
        }
        
    }
}

// funzione che elimina il nemico in una determinata colonna
void Lista_nemici::elimina_nemico(int id){
    ptr_nodo_nemici tmp = this->head;
    while(tmp != NULL && tmp->id != id){
        tmp = tmp->next;
    }
    if(tmp !=NULL){
        this->list_size--;
        if(tmp->prev != NULL){
            tmp->prev->next = tmp->next;
        }else{
            this->head = tmp->next; // elimina l'elemento in testa
        }
        if(tmp->next != NULL){
            tmp->next->prev = tmp->prev;
        }
        this->map->setChar(tmp->entity.x, tmp->entity.y, tmp->old_char);
        free(tmp);
    }
    printfile(this->head);
}



// da chiamare ogni tick
void Lista_nemici::muovi_nemici(void){
    this->nuove_direzioni();
    ptr_nodo_nemici tmp = this->head;
    while(tmp!=NULL){
        if(tmp->just_spawned == true){
            tmp->old_char = this->map->getRow(tmp->entity.y)->row[tmp->entity.x];
            this->map->setChar(tmp->entity.x, tmp->entity.y, ENEMY_CHAR); // forse qui va cambiato il carattere a seconda del tipo
            tmp->just_spawned = false;
            tmp = tmp->next;
        }else{
            if(tmp->prev == NULL){
                this->map->setChar(tmp->entity.x, tmp->entity.y, tmp->old_char);
            }else{
                if(tmp->prev->move_direction != SOTTO_DESTRA || tmp->prev->entity.x != tmp->entity.x || tmp->prev->entity.y != tmp->entity.y){
                    this->map->setChar(tmp->entity.x, tmp->entity.y, tmp->old_char);
                }
            }
            
            int newX = tmp->entity.x + (tmp->move_direction == SOTTO_DESTRA?1:0) - (tmp->move_direction == SOTTO_SINISTRA?1:0);
            int newY = tmp->entity.y - 1; // perche' i nemici vanno sempre e comunque sotto

            if(newY < 1 || newY < this->player->getY() - OFFSET){
                // il nemico e' in una posizione inferiore all'altezza del player o a quella della mappa quindi deve essere distrutto
                if(tmp->next != NULL){
                    tmp = tmp->next;
                    this->elimina_nemico(tmp->prev->id);
                }else{
                    this->elimina_nemico(tmp->id);
                    tmp = NULL;
                }
            }else{
                tmp->old_char = this->map->getRow(newY)->row[newX];
                if(tmp->old_char == ENEMY_CHAR){
                    tmp->old_char = tmp->next->old_char;
                }else if(tmp->old_char == '@'){ // questo else va tolto
                    tmp->old_char = ' ';
                }
                this->map->setChar(newX, newY, ENEMY_CHAR);
                tmp->entity.x = newX;
                tmp->entity.y = newY;
                tmp = tmp->next;
            }
        }
    }
    printfile(this->head);
}

// da chiamare ogni volta che si vuole far spawnare un nemico, max una volta a movimento dei nemici.
int Lista_nemici::calcola_spawnpos_X(void){
    if(this->list_size < ROW_DIM - 1){ // il -1 e' per il \0
        int numspace = ROW_DIM - this->list_size - 1;
        int spawnpos = (rand() % numspace) + 1;

        ptr_nodo_nemici tmp = this->head;
        int numero_spazi = 0;
        int finalX = -1; // se tmp == NULL allora tutto e' vuoto quindi spawnpos == entityX
        while(tmp != NULL && finalX == -1){
            if(tmp->prev == NULL){
                numero_spazi += tmp->entity.x;
            }else{
                numero_spazi += tmp->entity.x - tmp->prev->entity.x - 1;
            }
            if(numero_spazi >= spawnpos){
                finalX = tmp->entity.x - (numero_spazi - spawnpos) - 1;
            }else if(tmp->next == NULL){
                finalX = tmp->entity.x + (spawnpos - numero_spazi);
            }
            tmp = tmp->next;
        }
        if(finalX == -1){
            finalX = spawnpos - 1;
        }
        return finalX;

    }else{
        // non puo spawnare niente perche' non c'e' spazio
        return -1;
    }
}

Lista_proiettili::Lista_proiettili(void){
    this->head = NULL;
    this->current_id = 0;
}

void Lista_proiettili::aggiungi_proiettile(int x, int y, int direction){
    ptr_nodo_proiettili nuovo_proiettile = new nodo_proiettili;
    nuovo_proiettile->x = x;
    nuovo_proiettile->y = y;
    nuovo_proiettile->direction = direction;
    nuovo_proiettile->id = this->current_id + 1;
    this->current_id++;
    // la lista e' ordinata per righe, in testa il proiettile piu in alto e in coda quello piu in basso
    // l'ordine nella stessa riga non e' considerato, i proiettili sono sparsi
    ptr_nodo_proiettili tmp = this->head;
    if(tmp->y < nuovo_proiettile->y){
        nuovo_proiettile->next = tmp;
        nuovo_proiettile->prev = NULL;
        tmp->prev = nuovo_proiettile;
        this->head = nuovo_proiettile;
    }else{
        while(tmp->y >= nuovo_proiettile->y && tmp->next != NULL){
            tmp = tmp->next;
        }
        if(tmp->y < nuovo_proiettile->y){ // significa che tmp->next == NULL
            tmp->next = nuovo_proiettile;
            nuovo_proiettile->next = NULL;
            nuovo_proiettile->prev = tmp;
        }else{
            nuovo_proiettile->prev = tmp->prev;
            tmp->prev->next = nuovo_proiettile;
            nuovo_proiettile->next = tmp;
            tmp->prev = nuovo_proiettile;
        }
    }
}

void Lista_proiettili::elimina_proiettile(int id){
    ptr_nodo_proiettili tmp = this->head;
    while(tmp!=NULL){
        if(tmp->id == id){
            if(tmp->prev != NULL){
                tmp->prev->next = tmp->next;
            }
            if(tmp->next != NULL){
                tmp->next->prev = tmp->prev;
            }
            free(tmp);
            tmp = NULL;
        }else{
            tmp = tmp->next;
        }
    }
}

void Lista_proiettili::muovi_proiettili(void){
    ptr_nodo_proiettili tmp = this->head;
    bool exit = false;
    ptr_nodo_proiettili aux;
    while(tmp != NULL){
        tmp->y += (tmp->direction == SOPRA ? 1 : -1);
        // devi eliminare il proiettile
        if(tmp->y < 1){
            if(tmp->next == NULL){
                this->elimina_proiettile(tmp->id);
                tmp = NULL;
            }else {
                tmp = tmp->next;
                this->elimina_proiettile(tmp->prev->id);
            }
        }else{
            // questa parte mantiene ordinata la lista per righe
            // in testa il proiettile piu in alto e in coda quello piu in basso
            if(tmp->next != NULL){
                tmp->next->prev = tmp->prev;
            }
            if(tmp->prev != NULL){
                tmp->prev->next = tmp->next;
            }
            aux = (tmp->direction == SOPRA ? tmp->prev : tmp->next);
            exit = false;
            while(aux != NULL && !exit){
                if((aux->y >= tmp->y && tmp->direction == SOPRA) || (aux->y <= tmp->y && tmp->direction == SOTTO)){
                    if(tmp->direction == SOPRA){
                        tmp->prev = aux;
                        tmp->next = aux->next;
                        if(aux->next != NULL){
                            aux->next->prev = tmp;
                        }
                        aux->next = tmp;
                    }else{
                        tmp->next = aux;
                        if(aux->prev != NULL){
                            aux->prev->next = tmp;
                        }
                        tmp->prev = aux->prev;
                        aux->prev = tmp;
                    }
                    exit = true;
                }

                aux = (tmp->direction == SOPRA ? aux->prev:aux->next);
            }
        }
        
    }
}
