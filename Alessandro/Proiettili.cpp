/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "Proiettili.h"
using namespace constants;
using namespace std;

///// debug
#include <fstream>
// Queste funzioni servono per visualizzare meglio la lista
// salvandola in un file
string wheree(int n){
    switch(n){
        case SOTTO:
            return "SOTTO         ";
            break;
        case SOPRA:
            return "SOPRA         ";
        case SOTTO_SINISTRA:
            return "SOTTO_SINISTRA";
        default:
            return "NON_LO_SO     ";
    }
    return "NON_LO_SO     ";
}

void printfilee(ptr_nodo_proiettili lista){
  ofstream myfile;
  myfile.open ("lista.txt");
  int i = 0;
  while(lista!=NULL){
      myfile << to_string(i) << ") "<<(i>9?"":" ")<<"ID:"<<lista->id<<(lista->id>9? "":" ")<<" X:"<<to_string(lista->x)<<(lista->x>9?"":" ")<<" Y:"<<to_string(lista->y)<<(lista->y>9?"":" ")<<endl;
      i++;
      lista = lista->next;
  }
  myfile.close();
}
/////



Lista_proiettili::Lista_proiettili(Mappa *map){
    this->head = NULL;
    this->current_id = 0;
    this->map = map;
}

void Lista_proiettili::aggiungi_proiettile(int x, int y, int direction){
    ptr_nodo_proiettili nuovo_proiettile = new nodo_proiettili;
    nuovo_proiettile->x = x;
    nuovo_proiettile->y = y;
    nuovo_proiettile->direction = direction;
    nuovo_proiettile->id = this->current_id + 1;
    this->current_id++;
    // inserimento nella mappa del proiettile
    nuovo_proiettile->old_char = this->map->getRow(y)->row[x];
    this->map->setChar(x, y, PROIETTILE);

    // la lista e' ordinata per righe, in testa il proiettile piu in alto e in coda quello piu in basso
    // l'ordine nella stessa riga non e' considerato, i proiettili sono sparsi
    ptr_nodo_proiettili tmp = this->head;
    if(tmp == NULL){
        nuovo_proiettile->next = NULL;
        nuovo_proiettile->prev = NULL;
        this->head = nuovo_proiettile;
    }else if(tmp->y < nuovo_proiettile->y){
        nuovo_proiettile->next = tmp;
        nuovo_proiettile->prev = NULL;
        tmp->prev = nuovo_proiettile;
        this->head = nuovo_proiettile;
    }else{
        while(tmp->y >= nuovo_proiettile->y && tmp->next != NULL){
            tmp = tmp->next;
        }
        if(tmp->y < nuovo_proiettile->y){ // significa che tmp->next == NULL
            nuovo_proiettile->prev = tmp->prev;
            tmp->prev->next = nuovo_proiettile;
            nuovo_proiettile->next = tmp;
            tmp->prev = nuovo_proiettile;
        }else{
            tmp->next = nuovo_proiettile;
            nuovo_proiettile->next = NULL;
            nuovo_proiettile->prev = tmp;
        }
    }
    //debug
    printfilee(this->head);
    ////
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
    //debug
    printfilee(this->head);
    //////
}

char Lista_proiettili::set_and_retrieve(int x, int y, int old_char){
    ptr_nodo_proiettili tmp = this->head;
    while(tmp != NULL){
        if(tmp->x == x && tmp->y == y){
            char old = tmp->old_char;
            tmp->old_char = old_char;
            return old;
        }
        tmp = tmp->next;
    }
    return ' '; // non dovrebbe succedere
}

// la testa e' il proiettile piu in alto
// la lista e' ordinata per righe
void Lista_proiettili::muovi_proiettili(void){
    ptr_nodo_proiettili tmp = this->head;
    if(tmp != NULL){
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
    }
    bool exit = false;
    ptr_nodo_proiettili aux;

    while(tmp != NULL){
        // aggiorna mappa
        if(tmp->old_char != ENEMY_CHAR_ARTIGLIERE && tmp->old_char != ENEMY_CHAR_SOLD_SEMPLICE
           && tmp->old_char != ENEMY_CHAR_TANK && tmp->old_char != ENEMY_CHAR_BOSS){
            if(tmp->old_char == PLAYER){
                tmp->old_char = ' ';
            }
            this->map->setChar(tmp->x, tmp->y, tmp->old_char);
        }
        tmp->y += (tmp->direction == SOPRA ? 1 : -1);
        if(tmp->y < 1){ // non so se eliminare i proiettili se sono sotto al player
            if(tmp->prev == NULL){
                this->elimina_proiettile(tmp->id);
                tmp = NULL;
            }else {
                tmp = tmp->prev;
                this->elimina_proiettile(tmp->next->id);
            }
        }else{
            
            // spostamento nella mappa del proiettile
            tmp->old_char = this->map->getRow(tmp->y)->row[tmp->x];\
            if(tmp->old_char != ENEMY_CHAR_ARTIGLIERE && tmp->old_char != ENEMY_CHAR_SOLD_SEMPLICE
           && tmp->old_char != ENEMY_CHAR_TANK && tmp->old_char != ENEMY_CHAR_BOSS){
                this->map->setChar(tmp->x, tmp->y, PROIETTILE);
            }

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
                if(aux->next == NULL && tmp->direction == SOTTO && !exit){
                    aux->next = tmp;
                    tmp->next = NULL;
                    tmp->prev = aux;
                    aux = NULL;
                    exit = true;
                } else{
                    aux = (tmp->direction == SOPRA ? aux->prev:aux->next);
                }
            }
            if((tmp->next == NULL) && (tmp->prev == NULL)){
                this->head = tmp;
            }else if (!exit){
                if(tmp->direction == SOPRA){
                    tmp->prev = NULL;
                    tmp->next = this->head;
                    this->head = tmp;
                }else{
                    tmp->prev->next = tmp;
                    tmp->next = NULL;
                }
            }
            tmp = tmp->prev;
        }
        printfilee(this->head);
    }
    
}
