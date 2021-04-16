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
