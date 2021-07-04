#include "Bullet.h"
#include "Map.h"
#include "Player.h"
#include "costanti.hpp"

using namespace constants;
using namespace std;

/*  Author:         Alessandro Frau
    Parameters:     map -> puntatore alla mappa
                    p -> puntatore al player
    Return value:   void
    Comments:       Costruttore
*/
BulletList::BulletList(Map *map, Player *p){
    this->head = NULL;
    this->current_id = 0;
    this->map = map;
    this->player = p;
    this->special_bullet = 0;
    
}


/*  Author:         Alessandro Frau (Parte logica), Francesco apollonio (Parte di who_shot)
    Parameters:     x -> cordinata x in cui deve uscire il proiettile
                    y -> cordinata y in cui deve uscire il proiettile
                    direction -> la direzione in cui si sposta il proiettile (SOPRA o SOTTO)
                    who_shot -> Il codice del nemico che ha sparato (COD_BOSS, COD_TANK, ...)
    Return value:   void
    Comments:       Funzione che aggiunge un proiettile alla lista
                    - La lista e' ordinata per righe, quindi l'aggiunta
                        avviene nella posizione corretta
*/
void BulletList::add_bullet(int x, int y, int direction, int who_shot){
    ptr_bullet_node new_bullet = new BulletNode;
    new_bullet->x = x;
    new_bullet->y = y;
    new_bullet->direction = direction;
    new_bullet->already_moved = false;
    new_bullet->id = this->current_id + 1;
    this->current_id++;
    // determinazione del danno del proiettile
    if(who_shot == COD_BOSS) new_bullet->damage = DANNO_BOSS; //DANNO BOSS
    else if (who_shot == COD_TANK) new_bullet->damage = DANNO_TANK; //DANNO TANK
    else if (who_shot == COD_ARTIGLIERE) new_bullet->damage = DANNO_ARTIGLIERE; //DANNO ARTIGLIERE
    else if (who_shot == COD_SOLD_SEMPLICE) new_bullet->damage = DANNO_SOLD_SEMPLICE; //DANNO SOLDADO SEMPLICE
    else new_bullet->damage = DANNO_PLAYER; //DANNO CHE FA IL PLAYER QUANDO SPARA
    
    // inserimento nella mappa del proiettile
    new_bullet->old_char = this->map->get_row(y)->row[x];
    this->map->set_char(x, y, PROIETTILE);

    // la lista e' ordinata per righe, in testa il proiettile piu in alto e in coda quello piu in basso
    // l'ordine nella stessa riga non e' considerato, i proiettili sono sparsi
    ptr_bullet_node tmp = this->head;
    if(tmp == NULL){
        new_bullet->next = NULL;
        new_bullet->prev = NULL;
        this->head = new_bullet;
    }else if(tmp->y < new_bullet->y){
        new_bullet->next = tmp;
        new_bullet->prev = NULL;
        tmp->prev = new_bullet;
        this->head = new_bullet;
    }else{
        while(tmp->y >= new_bullet->y && tmp->next != NULL){
            tmp = tmp->next;
        }
        if(tmp->y < new_bullet->y){ // significa che tmp->next == NULL
            if(tmp->prev != NULL){
                tmp->prev->next = new_bullet;
            }
            new_bullet->prev = tmp->prev;
            new_bullet->next = tmp;
            tmp->prev = new_bullet;
        }else{
            tmp->next = new_bullet;
            new_bullet->next = NULL;
            new_bullet->prev = tmp;
        }
    }
}


/*  Author:         Alessandro Frau
    Parameters:     id -> id del proiettile da eliminare
    Return value:   void
    Comments:       Funzione che si occupa di eliminare il proiettile con l'id passato
*/
void BulletList::delete_bullet(int id){
    ptr_bullet_node tmp = this->head;
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
}

/*  Author:         Alessandro Frau
    Parameters:     x -> cordinata x del proiettile
                    y -> cordinata y del proiettile
                    old_char -> valore che verra' settato come nuovo old_char del proiettile
    Return value:   vecchio old_char del proiettile
    Comments:       setta l'old_char del proiettile a coordinate x, y, e ne restituisce l'old_char prima di essere modificato
*/
char BulletList::set_and_retrieve(int x, int y, int old_char){
    ptr_bullet_node tmp = this->head;
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

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   void
    Comments:       Funzione che fa sparare un proiettile a tutti i nemici contemporaneamente
*/
void BulletList::shoot_bullet(void){
    if(this->map->get_row(this->player->getY()+1)->row[this->player->getX()] != PROIETTILE){
        this->add_bullet(this->player->getX(), this->player->getY()+1, SOPRA, -1);
        // Attenzione: quando a sparare è il player la variabile "who_shot" viene settata
        // di default a -1
    }
}


/*  Author:         Francesco Apollonio 
    Parameters:     void
    Return value:   int
    Comments:       Funzione che restituisce il numero di proiettili speaciali disponibili.
*/


int BulletList::get_special_bullet(void){
       return this->special_bullet;
}

/*  Author:         Francesco Apollonio 
    Parameters:     int
    Return value:   void
    Comments:       Funzione che setta il numero di proiettili speaciali disponibili.
                    Viene chiamata nel momento in cui il player prende il bonus "proiettili speciali"
                    Il numero che viene settato è predefinito.
*/

void BulletList::set_special_bullet(int number){
    this->special_bullet = number;
}

    /*  Author:         Francesco Apollonio 
        Parameters:     void
        Return value:   int
        Comments:       La funzione restituisce la colonna sulla quale è presente un nemico da danneggiare.
                        Se nessun nemico dev'essere danneggiato il suo valore di default è -1.
    */

int BulletList::get_damage_enemy_x(void){
    return this->damage_enemy_x;
}


/*  Author:         Francesco Apollonio 
    Parameters:     int
    Return value:   void
    Comments:       La funzione modifica il parametro identificando così una colonna sulla quale
                    è presente un nemico da danneggiare.
*/


void BulletList::set_damage_enemy_x(int x){
    this->damage_enemy_x = x;
}

/*  Author:         Alessandro Frau (Parte logica), Francesco Apollonio (Parte legata al danno in base al tipo di nemico)
    Parameters:     void
    Return value:   restituisce il valore di end_game
    Comments:       - La funzione si occupa di muovere tutti i proiettili nelle giuste
                        posizioni, 
                    - La testa e' il proiettile piu in alto
                    - La lista e' ordinata per righe
*/
/* Spiegazione intuitiva algoritmo
    Partendo dal proiettile in testa si decidono le nuove coordinate del proiettile.
    - Per prima cosa si rimuove dalla mappa il carattere del proiettile vecchio
    - poi si verifica cosa e' presente nella nuova posizione
        - se e' presente il player allora si riduce la vita al player
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
bool BulletList::move_bullet(void){
    ptr_bullet_node tmp = this->head;
    bool collision;
    bool end_game = false;
    bool bullet_on_player = false;
    ptr_bullet_node aux;
    while(tmp != NULL){
        // aggiorna posizione vecchia proiettile nella mappa
        if(tmp->old_char != CHAR_ARTIGLIERE && tmp->old_char != CHAR_SOLD_SEMPLICE
           && tmp->old_char != CHAR_TANK && tmp->old_char != CHAR_BOSS){
            this->map->set_char(tmp->x, tmp->y, tmp->old_char);
        }
        tmp->y += (tmp->direction == SOPRA ? 1 : -1);
        char new_old_char = this->map->get_row(tmp->y)->row[tmp->x];
        // controlli per capire cosa e' presente nella nuova posizione
        if(new_old_char == PLAYER){
            //change health restituisce true se è il player è morto
            if( player->change_health(- ( tmp->damage ) ) == true ){
                tmp->old_char = DESTRUCT_PLAYER;
                end_game = true;                
            }else{
                tmp->old_char = PLAYER;
                //this->map->set_char(tmp->x, tmp->y, PLAYER);
                this->delete_bullet(tmp->id);          
                tmp=this->head;    
                bullet_on_player = true;                
            }

        }else if(new_old_char == PROIETTILE){
            tmp->old_char = this->set_and_retrieve(tmp->x, tmp->y, tmp->old_char);
        }else{
            tmp->old_char = new_old_char;
        }

       if (bullet_on_player == false) this->map->set_char(tmp->x, tmp->y, PROIETTILE);      
       
        // elimina proiettili out of bounds
        if (bullet_on_player == false){
            this->map->set_char(tmp->x, tmp->y, PROIETTILE);
        
            if( (tmp->y < 1 || tmp->y > this->map->get_total_height() - 1 ) ){ // non so se eliminare i proiettili se sono sotto al player
                this->map->set_char(tmp->x, tmp->y, tmp->old_char);
                if(tmp->next == NULL){
                    this->delete_bullet(tmp->id);
                    tmp = NULL;
                }else {
                    tmp = tmp->next;
                    this->delete_bullet(tmp->prev->id);
                }
            }else{
                tmp->already_moved = true;
                collision = false;
                ptr_bullet_node next = tmp->next; // salvare prossimo proiettile da muovere
                while(next != NULL && (next->already_moved || (next->y == tmp->y && next->x == tmp->x))){
                    next = next->next;
                }

                // Controllo collisioni con Bonus
                if(new_old_char == COD_BONUS_SALUTE || new_old_char == COD_BONUS_BOMBA || new_old_char == COD_MALUS_SALUTE || new_old_char == COD_BONUS_PROIETTILI_SPECIALI){
                    this->map->set_char(tmp->x, tmp->y, new_old_char);
                }
                //In questo modo il proiettile "passa sotto al Bonus"
 

                // controllo collisioni con altri proiettili o nemici
                if((new_old_char == CHAR_ARTIGLIERE || new_old_char == CHAR_BOSS || new_old_char == CHAR_SOLD_SEMPLICE || new_old_char == CHAR_TANK) && tmp->direction == SOPRA){ // proiettile del player sul nemico                                               
                    collision = true;
                    this->damage_enemy_x = tmp->x;
                    this->delete_bullet(tmp->id);

                }else if(tmp->direction == SOTTO){
                    aux = tmp->next;
                    while(aux != NULL && aux->y >= tmp->y && !collision){
                        if(tmp->y == aux->y && tmp->x == aux->x){
                            if(aux->direction == SOPRA){
                                this->map->set_char(aux->x, aux->y, aux->old_char);
                                this->delete_bullet(tmp->id);
                                this->delete_bullet(aux->id);
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
                                this->map->set_char(aux->x, aux->y, aux->old_char);
                                this->delete_bullet(tmp->id);
                                this->delete_bullet(aux->id);
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
                        ptr_bullet_node prev = (aux == NULL?tmp->prev:aux->prev);
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
        bullet_on_player = false;
    }
    tmp = this->head;
    while(tmp != NULL){
        tmp->already_moved = false;
        tmp = tmp->next;
    }
    return end_game;
}


