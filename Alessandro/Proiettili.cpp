/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "nemici.h"
#include "Proiettili.h"
#include "funzioni_alex/Gioco.h"
using namespace constants;
using namespace std;

///// for debug purpose//////////////////////////////////
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

void printfilee(ptr_nodo_proiettili lista, int speciali){
    ofstream myfile;
    myfile.open ("lista_proiettili.txt");
    int i = 0;
    while(lista!=NULL){
        myfile << to_string(i) << ") "<<(i>9?"":" ")<<"ID:"<<lista->id<<(lista->id>9? "":" ")<<" X:"<<to_string(lista->x)<<(lista->x>9?"":" ")<<" Y:"<<to_string(lista->y)<<(lista->y>9?"":" ")<<endl;
        i++;
        lista = lista->next;
    }
    myfile << "Num. Proiettili speciali -> " << speciali << endl;
    myfile.close();
}
///// end of debugging things ////////////////////////////


Lista_proiettili::Lista_proiettili(Mappa *map, Player *p){
    this->head = NULL;
    this->current_id = 0;
    this->map = map;
    this->player = p;
    this->proiettili_speciali = 0;
    
}

void Lista_proiettili::spara_player(void){
    if(this->map->getRow(this->player->getY()+1)->row[this->player->getX()] != PROIETTILE){
        this->aggiungi_proiettile(this->player->getX(), this->player->getY()+1, SOPRA, -1);
        //Attenzione: quando a sparare è il player la variabile "who_shot" viene settata
        //di default a -1
    }
}


// funzione che aggiunge un proiettile alla lista
// la lista e' ordinata per righe, quindi la funzione si occupa di
// aggiungere il proiettile nella posizione corretta
void Lista_proiettili::aggiungi_proiettile(int x, int y, int direction, int who_shot){
    ptr_nodo_proiettili nuovo_proiettile = new nodo_proiettili;
    nuovo_proiettile->x = x;
    nuovo_proiettile->y = y;
    nuovo_proiettile->direction = direction;
    nuovo_proiettile->already_moved = false;
    nuovo_proiettile->id = this->current_id + 1;
    this->current_id++;
    //determinazione del danno del proiettile
    if(who_shot == COD_BOSS) nuovo_proiettile->damage = DANNO_BOSS; //DANNO BOSS
    else if (who_shot == COD_TANK) nuovo_proiettile->damage = DANNO_TANK; //DANNO TANK
    else if (who_shot == COD_ARTIGLIERE) nuovo_proiettile->damage = DANNO_ARTIGLIERE; //DANNO ARTIGLIERE
    else if (who_shot == COD_SOLD_SEMPLICE) nuovo_proiettile->damage = DANNO_SOLD_SEMPLICE; //DANNO SOLDADO SEMPLICE
    else nuovo_proiettile->damage = DANNO_PLAYER; //DANNO CHE FA IL PLAYER QUANDO SPARA
    
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
            if(tmp->prev != NULL){
                tmp->prev->next = nuovo_proiettile;
            }
            nuovo_proiettile->prev = tmp->prev;
            nuovo_proiettile->next = tmp;
            tmp->prev = nuovo_proiettile;
        }else{
            tmp->next = nuovo_proiettile;
            nuovo_proiettile->next = NULL;
            nuovo_proiettile->prev = tmp;
        }
    }
    //debug
    printfilee(this->head, this->proiettili_speciali);
    ////
}
//Funzione che si occupa di eleminare il proiettile con l'id passato
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
            if(this->head->id == tmp->id){
                this->head = this->head->next;
            }
            free(tmp);
            tmp = NULL;
        }else{
            tmp = tmp->next;
        }
    }
    //debug
    printfilee(this->head, this->proiettili_speciali);
    //////
}
// setta l'old_char del proiettile a coordinate x, y, e ne restituisce l'old_char prima di essere modificato

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
    return SPAZIO_VUOTO; // non dovrebbe succedere
}

// funzione che si occupa di far muovere tutti i proiettili nelle giuste posizioni
// la testa e' il proiettile piu in alto
// la lista e' ordinata per righe
/* Spiegazione intuitiva algoritmo
    Partendo dal proiettile in testa si decidono le nuove coordinate del proiettile.
    - Per prima cosa si rimuove dalla mappa il carattere del proiettile vecchio
    - poi si verifica cosa e' presente nella nuova posizione
        - se e' presente il player allora il gioco finisce
        - se e' presente un altro proiettile allora si prende dal proiettile nuovo
          il carattere che era presente sotto di esso.
        - altrimenti si prende il carattere e lo si salva.
    - si aggiorna la mappa con il proiettile nella nuova posizione
    - Si verifica se il proiettile e' da eliminare perche' out of bound, altrimenti si va avanti
    - Si controlla se e' avvenuta una collisione tra due proiettili, in quel caso si eliminano entrambi
    - altrimenti si ricerca quale e' il prossimo proiettile da muovere e si salva
      (questo perche' alcuni proiettili possono andare avanti nella lista)
    - e si ricerca la nuova posizione nella lista del proiettile andando avanti fino al punto giusto
      facendo attenzione agli estremi.
*/
void Lista_proiettili::muovi_proiettili(void){
    ptr_nodo_proiettili tmp = this->head;
    bool collision;
    bool proiettile_on_player = false;
    ptr_nodo_proiettili aux;
    while(tmp != NULL){
        // aggiorna posizione vecchia proiettile nella mappa
        if(tmp->old_char != CHAR_ARTIGLIERE && tmp->old_char != CHAR_SOLD_SEMPLICE
           && tmp->old_char != CHAR_TANK && tmp->old_char != CHAR_BOSS){
            this->map->setChar(tmp->x, tmp->y, tmp->old_char);
        }
        tmp->y += (tmp->direction == SOPRA ? 1 : -1);
        char new_old_char = this->map->getRow(tmp->y)->row[tmp->x];
        // controlli per capire cosa e' presente nella nuova posizione
        if(new_old_char == PLAYER){
            //change health restituisce true se è il player è morto
            if( player->change_health(- ( tmp->damage ) ) == true ){
            tmp->old_char = DESTRUCT_PLAYER;
            end_game = true;                
            }
            else{
                tmp->old_char = PLAYER;
                //this->map->setChar(tmp->x, tmp->y, PLAYER);
                this->elimina_proiettile(tmp->id);          
                tmp=this->head;    
                proiettile_on_player = true;                
            }

        }else if(new_old_char == PROIETTILE){
            tmp->old_char = this->set_and_retrieve(tmp->x, tmp->y, tmp->old_char);
        }else{
            tmp->old_char = new_old_char;
        }

       if (proiettile_on_player == false) this->map->setChar(tmp->x, tmp->y, PROIETTILE);      
       
        // elimina proiettili out of bounds
        if (proiettile_on_player == false){
            this->map->setChar(tmp->x, tmp->y, PROIETTILE);
        
            if( (tmp->y < 1 || tmp->y > this->map->getTotalHeight() - 1 ) ){ // non so se eliminare i proiettili se sono sotto al player
                this->map->setChar(tmp->x, tmp->y, tmp->old_char);
                if(tmp->next == NULL){
                    this->elimina_proiettile(tmp->id);
                    tmp = NULL;
                }else {
                    tmp = tmp->next;
                    this->elimina_proiettile(tmp->prev->id);
                }
            }else{
                tmp->already_moved = true;
                collision = false;
                ptr_nodo_proiettili next = tmp->next; // salvare prossimo proiettile da muovere
                while(next != NULL && (next->already_moved || (next->y == tmp->y && next->x == tmp->x))){
                    next = next->next;
                }

                // Controllo collisioni con Bonus
                if(new_old_char == COD_BONUS_SALUTE || new_old_char == COD_BONUS_BOMBA || new_old_char == COD_MALUS_SALUTE || new_old_char == COD_BONUS_PROIETTILI_SPECIALI){
                    this->map->setChar(tmp->x, tmp->y, new_old_char);
                }
                //In questo modo il proiettile "passa sotto al Bonus"
 

                // controllo collisioni con altri proiettili o nemici
                if((new_old_char == CHAR_ARTIGLIERE || new_old_char == CHAR_BOSS || new_old_char == CHAR_SOLD_SEMPLICE || new_old_char == CHAR_TANK) && tmp->direction == SOPRA){ // proiettile personaggio sul nemico                                               
                    collision = true;
                    this->danneggia_nemico_x = tmp->x;
                    this->elimina_proiettile(tmp->id);

                }else if(tmp->direction == SOTTO){
                    aux = tmp->next;
                    while(aux != NULL && aux->y >= tmp->y && !collision){
                        if(tmp->y == aux->y && tmp->x == aux->x){
                            if(aux->direction == SOPRA){
                                this->map->setChar(aux->x, aux->y, aux->old_char);
                                this->elimina_proiettile(tmp->id);
                                this->elimina_proiettile(aux->id);
                                collision = true;
                            }
                        }
                        if(!collision){
                            aux = aux->next;
                        }
                    }
                }else{
                    aux = tmp->prev;
                    while(aux != NULL && aux->y <= tmp->y && !collision){
                        if(tmp->y == aux->y && tmp->x == aux->x){
                            if(aux->direction == SOTTO){
                                this->map->setChar(aux->x, aux->y, aux->old_char);
                                this->elimina_proiettile(tmp->id);
                                this->elimina_proiettile(aux->id);
                                collision = true;
                            }
                        }
                        if(!collision){
                            aux = aux->prev;
                        }
                    }
                }
                if(!collision){
                    // spostamento del proiettile nella lista
                    if(tmp->direction == SOPRA){
                        if(tmp->prev != NULL){
                            tmp->prev->next = tmp->next;
                        }
                        if(tmp->next != NULL){
                            tmp->next->prev = tmp->prev;
                        }
                        aux = tmp->prev;
                        while(aux != NULL && aux->y < tmp->y){
                            aux = aux->prev;
                        }
                        if(aux == NULL){
                            if(this->head->id == tmp->id){
                                if(tmp->next != NULL){
                                    tmp->next->prev = tmp;
                                }
                            }else{
                                tmp->next = this->head;
                                this->head->prev = tmp;
                            }
                            this->head = tmp;
                            tmp->prev = NULL;
                        }else{
                            if(aux->next != NULL){
                                aux->next->prev = tmp;
                            }
                            tmp->next = aux->next;
                            aux->next = tmp;
                            tmp->prev = aux;
                        }
                    }else{ // direction == SOTTO
                        if(tmp->prev != NULL){
                            tmp->prev->next = tmp->next;
                        }
                        if(tmp->next != NULL){
                            tmp->next->prev = tmp->prev;
                        }
                        aux = tmp->next;
                        ptr_nodo_proiettili prev = (aux == NULL?tmp->prev:aux->prev);
                        while(aux != NULL && aux->y > tmp->y){
                            prev = aux;
                            aux = aux->next;
                        }
                        if(aux == NULL){
                            if(prev == NULL){
                                this->head = tmp;
                                tmp->next = NULL;
                                tmp->prev = NULL;
                            }else{
                                prev->next = tmp;
                                tmp->prev = prev;
                                tmp->next = NULL;
                            }
                        }else{
                            tmp->prev = aux->prev;
                            if(aux->prev!=NULL){
                                aux->prev->next = tmp;
                            }
                            aux->prev = tmp;
                            tmp->next = aux;
                        }

                    }
                }
                tmp = next;
            }
        }
        proiettile_on_player = false;
        //debug
        printfilee(this->head, this->proiettili_speciali);
    }
    tmp = this->head;
    while(tmp != NULL){
        tmp->already_moved = false;
        tmp = tmp->next;
    }
   }
