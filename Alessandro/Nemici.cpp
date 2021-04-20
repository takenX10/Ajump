/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<string>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
#include "Nemici.h"
#include "Proiettili.h"

using namespace constants;
using namespace std;

#include <fstream>
///// debug
// Queste funzioni servono per visualizzare meglio la lista
// salvandola in un file
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

Nemico::Nemico(int pos_x = -1, int pos_y = -1){
    this->x = pos_x;
    this->y = pos_y;
    this->kind_of_enemy = kind_of_enemy;
    // Dal tipo di nemico posso già sapere vita e danno; inutile prenderli come ulteriori parametri.
    if (kind_of_enemy == 1) { this->health = 50; this->damage = 50; }
    else if (kind_of_enemy == 2) { this->health = 100; this->damage = 100; }
    else if (kind_of_enemy == 3) { this->health = 150; this->damage = 150; }
    else { this->health = 200; this->damage = 200;}
}

char Nemico::char_of_enemy(){
    if (kind_of_enemy == 1) return ENEMY_CHAR_SOLD_SEMPLICE;
    else if (kind_of_enemy == 2) return ENEMY_CHAR_ARTIGLIERE;
    else if (kind_of_enemy == 3) return ENEMY_CHAR_TANK;
    else return ENEMY_CHAR_BOSS;
}

void Nemico::change_health(int value){
    this->health += value;
}

void Nemico::change_damage(int value){
    this->damage += value;
}

void Nemico::update_position(int new_x, int new_y){
    this->x = new_x;
    this->y = new_y;
}
//funzione beta per la determinazione del tipo di nemico. 
void Nemico::decide_kindOfEnemy(int level){
    if(level > 1000) this->kind_of_enemy = 4; //Se siamo ad un livello più avanazato spawnano sempre boss (?)
    else{
        int boss_probability = rand() % RAND_MAX;
        if(boss_probability % 10 == 0) this->kind_of_enemy = 4; //ho il 10% di possibilità che spawni il BOSS
        else{ //se non è spawnato il boss allora calcolo quale altro nemico spawna
        //hanno tutti la stessa possibilità di spawnare. (33.3%)
            int probability = rand() % 3;
            if (probability == 0) this->kind_of_enemy = 1; //soldato semplice
            else if (probability == 1) this->kind_of_enemy = 2; // artigliere
            else if (probability == 2) this->kind_of_enemy = 3; // tank
        }
    }
}

Lista_nemici::Lista_nemici(Mappa *map, Player *p, Lista_proiettili *proiettili){
    this->head = NULL;
    this->map = map;
    this->player = p;
    this->list_size = 0;
    this->current_id = 0;
    this->proiettili = proiettili;
}

// aggiunta mantenendo ordine per colonne (in testa il nemico piu a sinistra e in coda quello piu a destra)
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
    if (this->head == NULL){    // lista vuota
        this->head = new_enemy;
        new_enemy->next = new_enemy->prev = NULL;
    }else{
        ptr_nodo_nemici tmp = this->head;
        while(tmp->next != NULL && tmp->entity.x < new_enemy->entity.x){ // vai avanti fino al punto giusto
            tmp = tmp->next;
        }
        if(tmp->entity.x > new_enemy->entity.x){
            if(tmp->prev == NULL){      // primo elemento
                this->head = new_enemy;
                new_enemy->prev = NULL;
                new_enemy->next = tmp;
                tmp->prev = new_enemy;
            }else{                      // elementi in mezzo
                tmp->prev->next = new_enemy;
                new_enemy->prev = tmp->prev;
                new_enemy->next = tmp;
                tmp->prev = new_enemy;
            }
        }else{ // ultimo elemento
            tmp->next = new_enemy;
            new_enemy->prev = tmp;
            new_enemy->next = NULL;
        }
    }
    // debug
    printfile(this->head);
    ///////
}

// elimina il nemico con l'id passato
// se l'id non e' presente non avviene nulla
void Lista_nemici::elimina_nemico(int id){
    ptr_nodo_nemici tmp = this->head;
    while(tmp != NULL && tmp->id != id){ // vai avanti fino al nemico giusto
        tmp = tmp->next;
    }
    if(tmp !=NULL){
        this->list_size--;
        if(tmp->prev != NULL){
            tmp->prev->next = tmp->next;
        }else{      // il nemico da eliminare e' in testa
            this->head = tmp->next;
        }
        if(tmp->next != NULL){
            tmp->next->prev = tmp->prev;
        }
        this->map->setChar(tmp->entity.x, tmp->entity.y, tmp->old_char);    // cancella il nemico dalla mappa
        free(tmp);
    }
    printfile(this->head);
}

// da chiamare ogni volta che si vogliono far muovere i nemici
// massimo una volta a "tick"
void Lista_nemici::muovi_nemici(void){
    this->nuove_direzioni();        // calcola le nuove direzioni degli elementi
    ptr_nodo_nemici tmp = this->head;
    //debug
    printfile(this->head);
    /////
    while(tmp!=NULL){
        if(tmp->just_spawned == true){  // nemico appena spawnato
            tmp->old_char = this->map->getRow(tmp->entity.y)->row[tmp->entity.x];
            this->map->setChar(tmp->entity.x, tmp->entity.y, tmp->entity.char_of_enemy());
            tmp->just_spawned = false;
            tmp = tmp->next;
        }else{
            // questo controllo esiste perche' se un nemico deve muoversi esattamente sopra nella stessa posizione
            // in cui e' presente un altro nemico, quando il nemico numero due si sposta resetta il carattere 
            // succede solo in caso i nemici vadano da sinistra a destra
            /* esempio
            ---------------- fase 1
            ....V..........
            .....V.........
            ...............
            ---------------- fase 2
            ................   
            .....V..........
            ......V.........
            ----------------
            in questo caso senza questo controllo il nemico piu in alto scomparirebbe.
            */
            
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
            }else{  // muovi nemico
                tmp->old_char = this->map->getRow(newY)->row[newX];
                if(tmp->old_char == tmp->entity.char_of_enemy()){
                    tmp->old_char = tmp->next->old_char;
                }else if(tmp->old_char == PLAYER){ // questo else va tolto debug
                    tmp->old_char = ' ';
                }else if(tmp->old_char == PROIETTILE){
                    tmp->old_char = this->proiettili->set_and_retrieve(newX, newY, tmp->entity.char_of_enemy());
                }
                this->map->setChar(newX, newY, tmp->entity.char_of_enemy());
                tmp->entity.update_position(newX, newY);
                tmp = tmp->next;
            }
        }
    }
    /*AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA*/
    // debug
    printfile(this->head);
    ///////
}

void Lista_nemici::spara(void){
    ptr_nodo_nemici tmp = this->head;
    while(tmp!=NULL){
        if(this->map->getRow(tmp->entity.y - 1)->row[tmp->entity.x] != PROIETTILE){
            this->proiettili->aggiungi_proiettile(tmp->entity.x, tmp->entity.y - 1, SOTTO);
        }
        tmp = tmp->next;
    }
}

// aggiorna il valore della variabile "move_direction" di ogni entita della lista
/* Spiegazione intuitiva algoritmo
tutti i nemici devono muoversi verso la posizione del player, con alcuni vincoli:
- ci puo essere massimo un nemico per colonna, quindi se il nemico nella colonna il nemico corrente si vuole spostare
  e' bloccato anche il nemico che si vuole spostare e' bloccato.

- se due nemici si vogliono spostare nella stessa colonna ha la priorita quello piu in basso

Per questi vincoli lo spostamento dei nemici risulta a cascata, quindi se il nemico a sinistra del 
player si muove, anche tutti quelli alla sua sinistra si muovono (eccetto casi elencati sotto), mentre 
quelli a destra devono controllare se hanno spazio libero altrimenti sono bloccati, e viceversa


L' algoritmo trova il nemico a sinistra piu vicino al player, ma non sopra, poi valuta
se il nemico a sinistra e' piu in basso di quello a destra inizia a spostarsi di conseguenza, settando come first tutti
i nemici che sono nel lato che si muove per "primo", e che quindi hanno la priorita, e setta come second i nemici
che si muovono come secondi. Valuta i nemici in ordine da quello piu vicino al player allontanandosi, facendo 
prima tutti quelli nel primo lato poi tutti quelli nel secondo lato, in questo modo si e' sicuri che 
tutti i nemici valutati si basino su valori gia aggiornati.
I casi in cui i nemici si muovono verso il basso sono:
    - il nemico e' appena spawnato
    - il nemico e' sopra il player 
    - la colonna in cui il nemico si vuole spostare e' occupata da un 
      altro nemico che va in basso, quindi non la libera. (quelli che si muovono per secondi)
*/
void Lista_nemici::nuove_direzioni(void){
    ptr_nodo_nemici tmp = this->head;
    if(tmp != NULL){
        int playerX = player->getX();
        while(tmp->next != NULL && tmp->next->entity.x < playerX){  // vai avanti fino al nemico piu vicino alla sinistra del player
            tmp = tmp->next;
        }
        ptr_nodo_nemici left = tmp;
        int fdir;   // direzione dei nemici che si muovono per "primi", 1 = destra, 0 = sinistra
        ptr_nodo_nemici right;
        ptr_nodo_nemici first;
        ptr_nodo_nemici second;
        if(tmp->next == NULL && tmp->entity.x <= playerX){  // setta left e right
            left = tmp;
            right = NULL;
        }else if(tmp->prev == NULL && tmp->entity.x > playerX){
            left = NULL;
            right = tmp;
        }else{
            left = tmp;
            right = tmp->next;
        }
        if(right == NULL){  // setta first e second
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
        while(first != NULL){ // decide la direzione dei nemici che si muovono per "primi"
            ptr_nodo_nemici next_node = (fdir == 1 ? first->next : first->prev); // il primo nemico nella direzione in cui il nodo corrente vuole spostarsi
            if(first->entity.x == playerX){
                first->move_direction = SOTTO;
            }else{
                int newdir = (fdir == 1 ? SOTTO_DESTRA : SOTTO_SINISTRA);
                if(next_node == NULL){  // non ci sono nemici in mezzo quindi spostati dove vuoi
                    first->move_direction = newdir;
                }else if(first->just_spawned == true){  // i nemici appena spawnati vanno sempre verso il basso
                    first->move_direction = SOTTO;
                }else if(next_node->entity.x == first->entity.x + (fdir == 1 ? 1 : -1)){
                    if(next_node->entity.x == playerX){ // questo controllo serve nel caso il PRIMO nemico controllato
                                                        // sia esattamente affianco al nemico sopra al player 
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
        while(second != NULL){  // intuitivamente molto simile a first, con qualche controllo in piu per colpa delle minori priorita
            ptr_nodo_nemici next_node = (fdir == 1 ? second->prev : second->next);
            int newdir = (fdir == 1 ? SOTTO_SINISTRA : SOTTO_DESTRA);
            if(second->entity.x == playerX){
                second->move_direction = SOTTO;
            }else if(second->just_spawned == true){
                second->move_direction = SOTTO;
            }else if(next_node != NULL){
                if(next_node->entity.x == second->entity.x + (fdir == 1 ? -2 : 2)){ // questo controllo serve per mantenere le priorita nel caso
                                                                                    // con due nemici che vanno nella stessa colonna
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

// restituisce la cordinata X in cui il nemico puo spawnare
// se non ci sono spazi restituisce -1
/* Spiegazione intuitiva algoritmo
    Conta quanti spazi vuoti sono liberi, e ne decide uno random in cui inserire il nemico
    Esempio: 
    la riga e' lunga 20 spazi, ci sono gia 10 nemici, quindi abbiamo 10 spazi vuoti (20 - 10)
    generiamo un numero random tra 1 e 10, per esempio 3, restituiamo la cordinata X del terzo spazio vuoto

    Per capire la cordinata si sposta nella lista un elemento alla volta, e conta quanti spazi vuoti
    sono presenti tra un elemento e l'altro, sottraendo la X dell'elemento corrente con quella di quello precedente
    finche' non trova l'offset giusto, quindi lo restituisce

*/
int Lista_nemici::calcola_spawnpos_X(void){
    if(this->list_size < ROW_DIM - 1){ // il -1 e' per il \0
        int num_free_spaces = ROW_DIM - this->list_size - 1; 
        int spawnpos = (rand() % num_free_spaces) + 1;  // il +1 e' perche' ∀a>=b, a%b restituisce valori da 0 a b-1, 
                                                        // ma a noi interessano da 1 a b, perche' spawnpos corrisponde all' nesimo spazio libero
        ptr_nodo_nemici tmp = this->head;
        int numero_spazi = 0;       // numero di spazi gia superati
        int finalX = -1; 
        while(tmp != NULL && finalX == -1){
            if(tmp->prev == NULL){          // primo elemento della lista
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
        // se finalX == -1 allora tmp == NULL, quindi tutti gli spazi sono vuoti
        // e il valore random corrispondera' alla cordinata della x (-1 perche' gli indici partono da 0)
        if(finalX == -1){   
            finalX = spawnpos - 1;
        }
        return finalX;

    }else{
        // non puo spawnare niente perche' non c'e' spazio
        return -1;
    }
}
