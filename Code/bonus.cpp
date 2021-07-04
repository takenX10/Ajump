#include "bonus.h"


using namespace constants;
using namespace std;

/*
NB. Commenti tecnici possono essere trovati nel file "bonus.h"
*/

Bonus::Bonus(Map *map, Player *player, EnemyList *nemici, BulletList *proiettili){
    this->map = map;
    this->player = player;
    this->nemico = nemici;
    this->head = NULL;
    this->current_id = 1;
    this->proiettili = proiettili;
    last_spawn_height = -1;
}

char Bonus::char_of_bonus(int kind_of_bonus){
    switch (kind_of_bonus) {
    case COD_BONUS_SALUTE:
        return BONUS_SALUTE;
        break;

    case COD_MALUS_SALUTE:
        return MALUS_SALUTE;
        break;

    case COD_BONUS_BOMBA:
        return BONUS_BOMBA;
        break;

    case COD_BONUS_PROIETTILI_SPECIALI:
        return BONUS_PROIETTILI_SPECIALI;
        break;

    default:
        return BONUS_SALUTE;
    } 
}

void Bonus::aggiungi_bonus(){
    srand(time(NULL)); 
    ptr_bonus nuovo_bonus = new nodo_bonus;
    nuovo_bonus->kind_of_bonus = (rand() % BONUS_TOTALI ) + 1; //Decisione del bonus da far spawnare
    int spawn_x = ROW_DIM / 2; //Centro della mappa, utile nell'algoritmo subito in basso.
    int spawn_y = this->player->getY() + 24; //Il 24 serve a determinare l'altezza rispetto alla posizione del player in cui spawnerà il bonus.
                                             //24 posizioni sopra il player, ovvero l'ultima riga generata della mappa (e NON ancora visibile al player).
    bool left = false;
    int shift = 1;

    /*
        Spiegazione intuitiva dell'algoritmo che determina la posizione dello spawn del bonus:
        Partendo dal centro, mi sposto prima a destra e poi a sinistra finchè non
        trovo una zona della mappa che soddisfi i miei parametri per lo spawn del bonus;
        uno spazio vuoto con sotto almeno due basi (in modo che il player possa arrivarci agevolmente)
    */

    while( ! (this->map->get_row(spawn_y)->row[spawn_x] == SPAZIO_VUOTO && this->map->get_row(spawn_y-1)->row[spawn_x] == PIATTAFORMA && this->map->get_row(spawn_y-3)->row[spawn_x] == PIATTAFORMA)){
        if(left == false){
            spawn_x = spawn_x + shift;
            left = true;
        }
        else{
            spawn_x = spawn_x - 2*shift;
            left = false;
            shift = shift + 1;
        }
    }
    nuovo_bonus->x = spawn_x;
    nuovo_bonus->y = spawn_y;
    nuovo_bonus->id = this->current_id;
    this->current_id ++;

    //Aggiungo il bonus appena creato alla lista.
    //Il bonus in testa è il primo ad essere spawnato, quello in coda l'ultimo.

    if(this->head == NULL){ //Caso in cui la lista è vuota
        this->head = nuovo_bonus;
        nuovo_bonus->next = NULL;
        nuovo_bonus->prev = NULL;
    }
    else{ //Caso in cui la lista non è vuota
        ptr_bonus tmp = this->head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = nuovo_bonus;
        nuovo_bonus->prev = tmp;
        nuovo_bonus->next = NULL;
        tmp = NULL; 
    }
    this->map->set_char(nuovo_bonus->x, nuovo_bonus->y, char_of_bonus(nuovo_bonus->kind_of_bonus) );
}

void Bonus::rimuovi_bonus(int id){
    ptr_bonus tmp = this->head;
    while(tmp->id != id){
        tmp = tmp->next;
    }

    if(tmp->prev == NULL){ //Primo elemento della lista
        this->head = tmp->next;
        if(this->head != NULL){
            this->head->prev = NULL;
        }
        free(tmp);
        tmp = NULL;
    }
    else if(tmp->next == NULL){ //Ultimo elemento della lista
        tmp->prev->next = NULL;
        free(tmp);
        tmp = NULL;
    }
    else{ // Zona centrale della lista
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
        tmp = NULL;
    }
}

// restituisce il valore di end_game
bool Bonus::esegui_bonus(int kind_of_bonus, int x, int y){
    bool end_game = false;
    if(kind_of_bonus == COD_BONUS_SALUTE){ 
        this->player->change_health(VALORE_BONUS_SALUTE); 
    }
    else if(kind_of_bonus == COD_BONUS_BOMBA){ 

        //Elimino tutti i nemici presenti nella mappa (NON i loro proiettili)
        ptr_enemy_node tmp = this->nemico->get_head();
        if(tmp != NULL){
            while(tmp->next != NULL){
                this->nemico->delete_enemy(tmp->next->id);
            }
            this->nemico->delete_enemy(tmp->id);  
        }
    }
    else if(kind_of_bonus == COD_MALUS_SALUTE){ 
       bool player_dead = this->player->change_health(VALORE_MALUS_SALUTE);
       if(player_dead == true){
           end_game = true;
       }
    }
    else if(kind_of_bonus == COD_BONUS_PROIETTILI_SPECIALI){
        proiettili->set_special_bullet(NUMERO_PROIETTILI_SPECIALI);
    }
    
    //Elimino il bonus dalla lista di quelli esistenti, in cui è salvato.
    ptr_bonus tmp = this->head;
    while( !(tmp->x == x && tmp->y == y) ){
        tmp = tmp->next;
    }
    rimuovi_bonus(tmp->id);
    tmp = NULL;

    return end_game;
}


void Bonus::set_last_spawn_height(int value){
    this->last_spawn_height = value;
}

int Bonus::get_last_spawn_height(void){
    return this->last_spawn_height;
}