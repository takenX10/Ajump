#include "Bonus.h"


using namespace constants;
using namespace std;

/*  Author:         Francesco Apollonio
    Parameters:     map -> mappa del gioco, necessaria per determinare i punti di spawn
                    player -> parametro necessario per modificare parametri del player come 'Health points'
                    nemici -> parametro necessario per operazioni sui nemici nel caso del bonus 'bomba'
                    proiettili -> parametro necessario per operazioni sui proiettili nel caso del bnonus 'proiettili speciali'
    Return value:   void
    Comments:       Costruttore.
*/

Bonus::Bonus(Map *map, Player *player, EnemyList *enemys, BulletList *bullets){
    this->map = map;
    this->player = player;
    this->enemy = enemys;
    this->head = NULL;
    this->current_id = 1;
    this->bullets = bullets;
    last_spawn_height = -1;
}


/*  Author:         Francesco Apollonio
    Parameters:     kind_of_bonus -> Codice identificativo del tipo di bonus.
    Return value:   char
    Comments:       La funzione restituisce il carattere, che verrà stampato nella mappa, del bonus corrisponente. 
*/

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



/*  Author:         Francesco Apollonio
    Parameters:     void
    Return value:   void
    Comments:       Spawn dei bonus ed aggiunta dei loro valori nella lista che li tiene in memoria.

    Spiegazione intuitiva dell'algoritmo che determina la posizione dello spawn del bonus:
    Partendo dal centro, mi sposto prima a destra e poi a sinistra finchè non
    trovo una zona della mappa che soddisfi i miei parametri per lo spawn del bonus;
    uno spazio vuoto con sotto almeno due basi (in modo che il player possa arrivarci agevolmente)
    
*/
void Bonus::add_bonus(){
    srand(time(NULL)); 
    ptr_bonus new_bonus = new bonus_node;
    new_bonus->kind_of_bonus = (rand() % BONUS_TOTALI ) + 1; //Decisione del bonus da far spawnare
    int spawn_x = ROW_DIM / 2; //Centro della mappa, utile nell'algoritmo subito in basso.
    int spawn_y = this->player->getY() + 24; //Il 24 serve a determinare l'altezza rispetto alla posizione del player in cui spawnerà il bonus.
                                             //24 posizioni sopra il player, ovvero l'ultima riga generata della mappa (e NON ancora visibile al player).
    bool left = false;
    int shift = 1;

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
    new_bonus->x = spawn_x;
    new_bonus->y = spawn_y;
    new_bonus->id = this->current_id;
    this->current_id ++;

    //Aggiungo il bonus appena creato alla lista.
    //Il bonus in testa è il primo ad essere spawnato, quello in coda l'ultimo.

    if(this->head == NULL){ //Caso in cui la lista è vuota
        this->head = new_bonus;
        new_bonus->next = NULL;
        new_bonus->prev = NULL;
    }
    else{ //Caso in cui la lista non è vuota
        ptr_bonus tmp = this->head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new_bonus;
        new_bonus->prev = tmp;
        new_bonus->next = NULL;
        tmp = NULL; 
    }
    this->map->set_char(new_bonus->x, new_bonus->y, char_of_bonus(new_bonus->kind_of_bonus) );
}



/*  Author:         Francesco Apollonio
    Parameters:     int id -> Id del bonus da eliminare. Ogni bonus ha un ID unico, utile alla sua identificazione.
    Return value:   void
    Comments:       Ricerca un bonus tramite il suo ID e lo rimuove dalla lista.
*/
void Bonus::remove_bonus(int id){
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




/*  Author:         Francesco Apollonio
    Parameters:     kind_of_bonus -> Tipologia del bonus da eseguire; Ogni bonus ha un codice corrispondente utile ad identificarlo.
                    x, y -> Parametri indicanti la posizione del bonus.
    Return value:   restituisce il valore di end_game
    Comments:       La funzione esegue il bonus, eseguendo gli 'effetti' corrispondenti; Quindi elimina il bonus dalla mappa e della lista (richiamando la funzione di cui sopra)
*/
bool Bonus::exec_bonus(int kind_of_bonus, int x, int y){
    bool end_game = false;
    if(kind_of_bonus == COD_BONUS_SALUTE){ 
        this->player->change_health(VALORE_BONUS_SALUTE); 
    }
    else if(kind_of_bonus == COD_BONUS_BOMBA){ 

        //Elimino tutti i nemici presenti nella mappa (NON i loro proiettili)
        ptr_enemy_node tmp = this->enemy->get_head();
        if(tmp != NULL){
            while(tmp->next != NULL){
                this->enemy->delete_enemy(tmp->next->id);
            }
            this->enemy->delete_enemy(tmp->id);  
        }
    }
    else if(kind_of_bonus == COD_MALUS_SALUTE){ 
       bool player_dead = this->player->change_health(VALORE_MALUS_SALUTE);
       if(player_dead == true){
           end_game = true;
       }
    }
    else if(kind_of_bonus == COD_BONUS_PROIETTILI_SPECIALI){
        bullets->set_special_bullet(NUMERO_PROIETTILI_SPECIALI);
    }
    
    //Elimino il bonus dalla lista di quelli esistenti, in cui è salvato.
    ptr_bonus tmp = this->head;
    while( !(tmp->x == x && tmp->y == y) ){
        tmp = tmp->next;
    }
    remove_bonus(tmp->id);
    tmp = NULL;

    return end_game;
}



/*  Author:         Francesco Apollonio
    Parameters:     value -> valore rappresentante l'altezza (nella mappa) in cui è stato fatto spawnare l'ultimo bonus.
    Return value:   void
    Comments:       il setting di questo parametro è utile ad evitare lo spawn di più bonus nello stesso punto (livello) della mappa. 
*/
void Bonus::set_last_spawn_height(int value){
    this->last_spawn_height = value;
}



/*  Author:         Francesco Apollonio
    Parameters:     void
    Return value:   int
    Comments:       La funzione restituisce il valore del parametro 'last_spawn_height' 
*/
int Bonus::get_last_spawn_height(void){
    return this->last_spawn_height;
}