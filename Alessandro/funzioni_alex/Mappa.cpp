#include <iostream>
#include "Mappa.h"
#include "print_functions.h"
#include "Alex_constants.hpp"
using namespace std;
using namespace constants;

Mappa::Mappa(int map_height /*= 0*/, int map_width /*= 0*/){
    //ptr_Map tmp = map_head;  // uso tmp perché map verrà aggiornato e non punterà più alla riga 0
    this->map_height = map_height;
    this->map_width = map_width;
    this->map_head = NULL;
    this->map_tail = NULL;
    this->total_height = 0;
    for(int i=0; i < this->map_height; i++){
        this->newRow();
    }
}
void Mappa::newRow(void){
    if(this->map_head == NULL){
        this->map_head = new Map;
        this->map_head->next = NULL;
        this->map_head->prev = NULL;
        this->map_head->num_row = 0;

        for(int i=0; i < this->map_width-1; i++){ 
            this->map_head->row[i] = PIATTAFORMA; 
        }
        this->map_head->row[this->map_width-1] = '\0';
        this->map_tail = this->map_head;
        this->total_height = this->map_tail->num_row;
    }else{
        ptr_Map new_row = new Map;               // "collego" la nuova riga all'ultima riga generata
        this->map_tail->next = new_row;
        new_row->num_row = this->map_tail->num_row+1;
        new_row->prev = this->map_tail; 
        new_row->next = NULL;
        
        if(new_row->num_row % 2 != 0){ // caso riga in cui NON vanno inserite piattaforme
            for(int i=0; i<this->map_width-1; i++) { new_row->row[i] = ' '; }
        }else{
            if(new_row->num_row % CHECKPOINT_ROW == 0){
                for(int i=0; i<this->map_width; i++) {     // piano "checkpoint" con piattaforma a larghezza max
                    new_row->row[i] = PIATTAFORMA;
                }
            }else{
                /* avrei scelto un approccio piu estendibile, nella forma di
                for(i = 0, i < NUM_PIATTAFORME; i++){
                    dim[i] = ...;
                    space[i] = ...;
                }
                fai_cose(dim, space);
                */
                // FALLO.
                int dim_1 = rand() % (ROW_DIM/4) +1; // dimensioni piattaforme
                int dim_2 = rand() % (ROW_DIM/4) +2;
                int dim_3 = rand() % (ROW_DIM/4) +2;
                int space_1 = rand() % 6 +1;         // spazi tra le piattaforme
                int space_2 = rand() % 3 +1;
                int space_3 = rand() % 2 +1;
                int i=0;
                // riempimento riga
                for(i=0; i<space_1; i++){ new_row->row[i] = ' '; }
                for(i=i; i<space_1 + dim_1; i++){ new_row->row[i] = PIATTAFORMA; }
                for(i=i; i<space_1 + dim_1 + space_2; i++){ new_row->row[i] = ' '; }
                for(i=i; i<space_1 + dim_1 + space_2 + dim_2; i++){ new_row->row[i] = PIATTAFORMA; }
                for(i=i; i<space_1 + dim_1 + space_2 + dim_2 + space_3; i++){ new_row->row[i] = ' '; }
                for(i=i; i<space_1 + dim_1 + space_2 + dim_2 + space_3 + dim_3; i++){ new_row->row[i] =PIATTAFORMA; }
                for(i=i; i<ROW_DIM-1; i++){ new_row->row[i] = ' '; }
            }
        }
        new_row->row[ROW_DIM-1] = '\0';
        this->map_tail = new_row;
        this->total_height = this->map_tail->num_row;
    }
}

/*  
    INFO: stampa di una "schermata", ovvero di MAP_HEIGHT piani
    PARAMETRI: puntatore alla testa della mappa (row numero 0), posizione giocatore
    RETURN: void    
*/
void Mappa::printMap(int top_line){
    ptr_Map map = this->map_tail;
    if(this->map_tail->num_row + 1< top_line){
        cout<<this->map_tail->num_row<<"<= "<<top_line - 1<<endl;
        cout << "ERROR: WRONG TOP LINE"<<endl;
        return;
    }
    while(map->num_row + 1 > top_line){
        map = map->prev;
    }
    for(int i=0; i<this->map_height; i++){
        for(int j=0; j<this->map_width; j++){
            if(findChar(j,i) != map->row[j]){
                moveCursor(j,i);
                cout << map->row[j];
            }
        }
        cout << MURO << " " << map->num_row;
        map = map->prev;
    }
}

ptr_Map Mappa::getRow(int n){
    ptr_Map tmp = this->map_tail;
    if(n > tmp->num_row){
        cout << "ERROR: LA RIGA NON ESISTE";
        return NULL;
    }
    while(tmp->num_row > n){
        tmp = tmp->prev;
    }
    return tmp;
}

void Mappa::setChar(int x, int y, char c){
    ptr_Map tmp = this->map_tail;
    
    if(y > tmp->num_row){
        cout << "ERROR: LA RIGA NON ESISTE";
    }else{
        while(tmp->num_row > y){
            tmp = tmp->prev;
        }
        tmp->row[x] = c;
    }
}
int Mappa::getWidth(void){ return this->map_width; }
int Mappa::getHeight(void){ return this->map_height; }
int Mappa::getTotalHeight(void){return this->total_height;}