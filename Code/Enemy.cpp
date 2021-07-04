#include <ctime>
#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "costanti.hpp"
#include "Bullet.h"

using namespace constants;
using namespace std;

/*  Author:         Alessandro Frau
    Parameters:     pos_x -> cordinata x del nemico
                    pos_y -> cordinata y del nemico
                    kind_of_enemy -> tipo di nemico (COD_TANK, COD_ARTIGLIERE, ....)
    Return value:   void
    Comments:       Costruttore della classe Enemy
*/
Enemy::Enemy(int pos_x = -1, int pos_y = -1, int kind_of_enemy = 1){
    this->x = pos_x;
    this->y = pos_y;
    this->kind_of_enemy = kind_of_enemy;
    if (kind_of_enemy == COD_SOLD_SEMPLICE) { this->health = VITA_SOLD_SEMPLICE; this->damage = DANNO_SOLD_SEMPLICE; }
    else if (kind_of_enemy == COD_ARTIGLIERE) { this->health = VITA_ARTIGLIERE; this->damage = DANNO_ARTIGLIERE; }
    else if (kind_of_enemy == COD_TANK) { this->health = VITA_TANK; this->damage = DANNO_TANK; }
    else { this->health = VITA_BOSS; this->damage = DANNO_BOSS; }
}

/*  Author:         Francesco Apollonio
    Parameters:     void
    Return value:   carattere del nemico 
    Comments:       Restituisce il carattere legato al nemico
*/
char Enemy::char_of_enemy(void){
    if (kind_of_enemy == COD_SOLD_SEMPLICE) return CHAR_SOLD_SEMPLICE;
    else if (kind_of_enemy == COD_ARTIGLIERE) return CHAR_ARTIGLIERE;
    else if (kind_of_enemy == COD_TANK) return CHAR_TANK;
    else return CHAR_BOSS;
}

/*  Author:         Francesco Apollonio
    Parameters:     value -> valore da aggiungere alla vita del nemico
    Return value:   void
    Comments:       Aggiunge il valore passato alla vita del nemico
*/
void Enemy::change_health(int value){
    this->health += value;
}

/*  Author:         Alessandro Frau
    Parameters:     new_x -> nuova cordinata x del nemico
                    new_y -> nuova cordinata y del nemico
    Return value:   void
    Comments:       Cambia le cordinate del nemico con quelle passate
*/
void Enemy::update_position(int new_x, int new_y){
    this->x = new_x;
    this->y = new_y;
}

/*  Author:         Francesco Apollonio
    Parameters:     level -> il livello corrente, serve per determinare la difficolta
    Return value:   Tipo di nemico estratto
    Comments:       Funzione che si occupa di restituire il tipo di nemico far spawnare
*/
int Enemy::decide_kind_of_enemy(int level){
    srand(time(NULL));
    if(level > DIFFICOLTA_ESTREMA) this->kind_of_enemy = COD_BOSS; //Incremento notevole della difficoltà facendo spawnare sempre BOSS
    else{
        int random_number = rand() % 9; //In questo modo gestisco al meglio la frequenza con cui voglio che spawni un nemico piuttosto che un altro
        if(random_number == 0) this->kind_of_enemy = COD_BOSS; //Ho circa il 10% di possibilità che spawni il BOSS
        //Ho il 33% circa di probabilità che spawni oguno degli altri nemici.
        else if (random_number > 0 && random_number < 4) this->kind_of_enemy = COD_TANK; 
        else if (random_number > 3 && random_number < 7) this->kind_of_enemy = COD_ARTIGLIERE;
        else kind_of_enemy = COD_SOLD_SEMPLICE;      
    }
    return this->kind_of_enemy;
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   this->x
    Comments:       funzione che restituisce la cordinata x del nemico
*/
int Enemy::get_x(void){
    return this->x;
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   this->y
    Comments:       funzione che restituisce la cordinata y del nemico
*/
int Enemy::get_y(void){
    return this->y;
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   this->health
    Comments:       funzione che restituisce la vita del nemico
*/
int Enemy::get_health(void){
    return this->health;
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   this->kind_of_enemy
    Comments:       funzione che restituisce il tipo del nemico
*/
int Enemy::get_kind_of_enemy(void){
    return this->kind_of_enemy;
}

/*  Author:         Alessandro Frau
    Parameters:     map -> puntatore alla mappa
                    p -> puntatore al player
                    proiettili -> puntatore alla classe che gestisce la lista di proiettili
    Return value:   void
    Comments:       Costruttore della classe EnemyList
*/
EnemyList::EnemyList(Map *map, Player *p, BulletList *proiettili){
    this->head = NULL;
    this->map = map;
    this->player = p;
    this->list_size = 0;
    this->current_id = 0;
    this->proiettili = proiettili;
}

/*  Author:         Alessandro Frau
    Parameters:     enemy -> Classe nemico da aggiungere
    Return value:   void
    Comments:       Aggiunge un nemico alla lista di nemici, mantenendo delle caratteristiche:
                    - La lista e' ordinata per colonne (in testa il nemico piu a sinistra e in coda quello piu a destra)
                    - Si da per scontato che nella colonna non sia presente nessun altro nemico, questo perche'
                      per decidere la cordinata x del nemico si deve utilizzare la funzione get_spawnpos_x().
*/
void EnemyList::add_enemy(Enemy enemy){
    this->list_size++;
    ptr_enemy_node new_enemy = new enemy_node;
    new_enemy->entity = enemy;
    new_enemy->id = this->current_id;
    this->current_id++;
    if (this->head == NULL){    // lista vuota
        this->head = new_enemy;
        new_enemy->next = new_enemy->prev = NULL;
    }else{
        ptr_enemy_node tmp = this->head;
        while(tmp->next != NULL && tmp->entity.get_x() < new_enemy->entity.get_x()){ // vai avanti fino al punto giusto
            tmp = tmp->next;
        }
        if(tmp->entity.get_x() > new_enemy->entity.get_x()){
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

}

/*  Author:         Alessandro Frau
    Parameters:     id -> id del nemico da eliminare
    Return value:   void
    Comments:       Elimina dalla lista di nemici quello con l'id passato, se non e' presente neanche un nemico con quell'id
                    non elimina nulla.
*/
void EnemyList::delete_enemy(int id){
    ptr_enemy_node tmp = this->head;
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
        this->map->set_char(tmp->entity.get_x(), tmp->entity.get_y(), tmp->old_char);    // cancella il nemico dalla mappa
        free(tmp);
    }
}

/*  Author:         Francesco Apollonio
    Parameters:     cordinata x del nemico
    Return value:   void
    Comments:       Funzione che riduce la vita del nemico alla cordinata x passata, in base al danno del proiettile del player.
*/
void EnemyList::damage_enemy_x(int x){
    ptr_enemy_node tmp = this->head;
    while(tmp != NULL && tmp->entity.get_x() != x){ // vai avanti fino al nemico giusto
        tmp = tmp->next;
    }
    if(tmp != NULL){
        if(proiettili->get_special_bullet() > 0){
            tmp->entity.change_health( -(DANNO_PROIETT_SPECIALE) );
        }
        else{
            tmp->entity.change_health( -(this->player->damage) ); 
        }
    }
    
    if(tmp != NULL){
        int vita = tmp->entity.get_health();
        if(tmp->entity.get_health() < 1){ 
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
                this->map->set_char(tmp->entity.get_x(), tmp->entity.get_y(), tmp->old_char);    // cancella il nemico dalla mappa
                free(tmp);
            }
        }
        else{
            this->map->set_char(tmp->entity.get_x(), tmp->entity.get_y(),tmp->entity.char_of_enemy()); 
        }
    }

}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   restituisce il valore di end_game
    Comments:       Funzione che fa muovere tutti i nemici all'unisono verso il player, facendo in
                    modo che nessun nemico sia nella stessa colonna dell'altro. Questa funzione deve
                    venire chiamata massimo una volta a tick.
*/
bool EnemyList::move_enemy(void){
    bool end_game = false;
    this->new_directions();        // calcola le nuove direzioni degli elementi
    ptr_enemy_node tmp = this->head;
    
    while(tmp!=NULL){
        if(tmp->just_spawned == true){  // nemico appena spawnato
            tmp->old_char = this->map->get_row(tmp->entity.get_y())->row[tmp->entity.get_x()];
            this->map->set_char(tmp->entity.get_x(), tmp->entity.get_y(), tmp->entity.char_of_enemy());
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
                this->map->set_char(tmp->entity.get_x(), tmp->entity.get_y(), tmp->old_char);
            }else{
                if(tmp->prev->move_direction != SOTTO_DESTRA || tmp->prev->entity.get_x() != tmp->entity.get_x() || tmp->prev->entity.get_y() != tmp->entity.get_y()){
                    this->map->set_char(tmp->entity.get_x(), tmp->entity.get_y(), tmp->old_char);
                }
            }

            int newX = tmp->entity.get_x() + (tmp->move_direction == SOTTO_DESTRA?1:0) - (tmp->move_direction == SOTTO_SINISTRA?1:0);
            int newY = tmp->entity.get_y() - 1; // perche' i nemici vanno sempre e comunque sotto

            if(newY < 1 || newY < this->player->getY() - OFFSET){
                // il nemico e' in una posizione inferiore all'altezza del player o a quella della mappa quindi deve essere distrutto
                if(tmp->next != NULL){
                    tmp = tmp->next;
                    this->delete_enemy(tmp->prev->id);
                }else{
                    this->delete_enemy(tmp->id);
                    tmp = NULL;
                }
            }else{  // muovi nemico
                tmp->old_char = this->map->get_row(newY)->row[newX];
                if(tmp->old_char == tmp->entity.char_of_enemy()){
                    tmp->old_char = tmp->next->old_char;
                }     
                else if(tmp->old_char == PLAYER){
                    end_game = true;
                    tmp->old_char = SPAZIO_VUOTO;
                }else if(tmp->old_char == PROIETTILE){
                    tmp->old_char = this->proiettili->set_and_retrieve(newX, newY, tmp->entity.char_of_enemy());
                }
                this->map->set_char(newX, newY, tmp->entity.char_of_enemy());
                tmp->entity.update_position(newX, newY);
                tmp = tmp->next;
            }
        }
    }
    return end_game;
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   restituisce il valore di end_game
    Comments:       Fa sparare a tutti i nemici all'unisono un proiettile
*/
bool EnemyList::shoot(void){
    bool end_game = false;
    ptr_enemy_node tmp = this->head;
    while(tmp!=NULL){
        if(tmp->entity.get_y() >2){
            char oldchar = this->map->get_row(tmp->entity.get_y() - 1)->row[tmp->entity.get_x()];
            if(oldchar != PROIETTILE && oldchar != PLAYER){
                this->proiettili->add_bullet(tmp->entity.get_x(), tmp->entity.get_y() - 1, SOTTO, tmp->entity.get_kind_of_enemy());
            }else{
                if(oldchar == PLAYER){
                    end_game = true;

                }
            }
        }
        tmp = tmp->next;
    }
    return end_game;
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   void
    Comments:       Aggiorna il valore della variabile move_direction per ogni nemico della lista
*/
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
void EnemyList::new_directions(void){
    ptr_enemy_node tmp = this->head;
    if(tmp != NULL){
        int playerX = player->getX();
        while(tmp->next != NULL && tmp->next->entity.get_x() < playerX){  // vai avanti fino al nemico piu vicino alla sinistra del player
            tmp = tmp->next;
        }
        ptr_enemy_node left = tmp;
        int fdir;   // direzione dei nemici che si muovono per "primi", 1 = destra, 0 = sinistra
        ptr_enemy_node right;
        ptr_enemy_node first;
        ptr_enemy_node second;
        if(tmp->next == NULL && tmp->entity.get_x() <= playerX){  // setta left e right
            left = tmp;
            right = NULL;
        }else if(tmp->prev == NULL && tmp->entity.get_x() > playerX){
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
        }else if(left->entity.get_y() > right->entity.get_y()){
            first = right;
            second = left;
            fdir = 0;
        }else{
            first = left;
            second = right;
            fdir = 1;
        }
        while(first != NULL){ // decide la direzione dei nemici che si muovono per "primi"
            ptr_enemy_node next_node = (fdir == 1 ? first->next : first->prev); // il primo nemico nella direzione in cui il nodo corrente vuole spostarsi
            if(first->entity.get_x() == playerX){
                first->move_direction = SOTTO;
            }else{
                int newdir = (fdir == 1 ? SOTTO_DESTRA : SOTTO_SINISTRA);
                if(next_node == NULL){  // non ci sono nemici in mezzo quindi spostati dove vuoi
                    first->move_direction = newdir;
                }else if(first->just_spawned == true){  // i nemici appena spawnati vanno sempre verso il basso
                    first->move_direction = SOTTO;
                }else if(next_node->entity.get_x() == first->entity.get_x() + (fdir == 1 ? 1 : -1)){
                    if(next_node->entity.get_x() == playerX){ // questo controllo serve nel caso il PRIMO nemico controllato
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
            ptr_enemy_node next_node = (fdir == 1 ? second->prev : second->next);
            int newdir = (fdir == 1 ? SOTTO_SINISTRA : SOTTO_DESTRA);
            if(second->entity.get_x() == playerX){
                second->move_direction = SOTTO;
            }else if(second->just_spawned == true){
                second->move_direction = SOTTO;
            }else if(next_node != NULL){
                if(next_node->entity.get_x() == second->entity.get_x() + (fdir == 1 ? -2 : 2)){ // questo controllo serve per mantenere le priorita nel caso
                    // con due nemici che vanno nella stessa colonna
                    if(next_node->move_direction == SOTTO || next_node->move_direction == newdir){
                        second->move_direction = newdir;
                    }else{
                        second->move_direction = SOTTO;
                    }
                }else if(next_node->entity.get_x() == second->entity.get_x() + (fdir == 1 ? -1 : 1)){
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

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   Cordinata in cui il nemico puo spawnare 
    Comments:       Restituisce la cordinata x in cui il nemico puo spawnare, -1 se non ci sono spazi disponibili
*/
/* Spiegazione intuitiva algoritmo
    Conta quanti spazi vuoti sono liberi, e ne decide uno random in cui inserire il nemico
    Esempio:
    la riga e' lunga 20 spazi, ci sono gia 10 nemici, quindi abbiamo 10 spazi vuoti (20 - 10)
    generiamo un numero random tra 1 e 10, per esempio 3, restituiamo la cordinata X del terzo spazio vuoto

    Per capire la cordinata si sposta nella lista un elemento alla volta, e conta quanti spazi vuoti
    sono presenti tra un elemento e l'altro, sottraendo la X dell'elemento corrente con quella di quello precedente
    finche' non trova l'offset giusto, quindi lo restituisce

*/
int EnemyList::calculate_spawnpos_x(void){
    if(this->list_size < ROW_DIM - 1){ // il -1 e' per il \0
        int num_free_spaces = ROW_DIM - this->list_size - 1;
        int spawnpos = (rand() % num_free_spaces) + 1;  // il +1 e' perche' ∀a>=b, a%b restituisce valori da 0 a b-1,
        // ma a noi interessano da 1 a b, perche' spawnpos corrisponde all' nesimo spazio libero
        ptr_enemy_node tmp = this->head;
        int numero_spazi = 0;       // numero di spazi gia superati
        int finalX = -1;
        while(tmp != NULL && finalX == -1){
            if(tmp->prev == NULL){          // primo elemento della lista
                numero_spazi += tmp->entity.get_x();
            }else{
                numero_spazi += tmp->entity.get_x() - tmp->prev->entity.get_x() - 1;
            }
            if(numero_spazi >= spawnpos){
                finalX = tmp->entity.get_x() - (numero_spazi - spawnpos) - 1;
            }else if(tmp->next == NULL){
                finalX = tmp->entity.get_x() + (spawnpos - numero_spazi);
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

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   this->head
    Comments:       funzione che restituisce testa della lista
*/
ptr_enemy_node EnemyList::get_head(void){
    return this->head;
}