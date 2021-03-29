/*
@ Author: Alex Lorenzato
*/
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include "Alex_character_editing.hpp"
#include "Alex_constants.hpp"

using namespace std;
using namespace constants;
// INFO GENERALI

// le funzioni hanno una notazione del tipo nomeFunzione, i parametri hano una notazione del tipo nome_parametro
// (char) 196  ->  simbolo usato per le piattaforme

// NOTE DA TENERE A MENTE DURANTE LO SVILUPPO

// per salire o scendere di livello nelle piattaforme ho fatto un controllo in cui devo avere (char) 196 perché la condizione di potermi muovere
// sia verificata, perciò se c'è un nemico/bonus/proiettile che sostituisce il carattere potrei non essere in grado di muovermi in quanto la piattaforma
// è "coperta" e non ho (char) 196 ma un altro carattere
// questo problema sarà riscontrato nella funzione checkPlatformProximity e contrassegno con <!> il punto in cui eventualmente andranno fatte modifiche
// probabile che lo stesso problema salterà fuori su checkMovementPossibility, quando controllo se posso muovermi a dx/sx diuna piattaforma
// in quanto il controllo viene fatto con (char) 196 perciò solo se c'è il carattere di una piattaforma mi lascerà muovermi
// ma se ci fosse ad esempio un bonus in mezzo a una piattaforma, non mi lascerebbe prenderlo


struct Map{
    char row[ROW_DIM];
    long int num_row;    // identificatore univoco riga
    Map* prev;
    Map* next;
};
typedef Map* ptr_Map;

class Mappa{
    private:
        ptr_Map map_head;
        ptr_Map map_tail;
        int map_height;
        int map_width;

    public:
        Mappa(int map_height = 0, int map_width = 0){
            //ptr_Map tmp = map_head;  // uso tmp perché map verrà aggiornato e non punterà più alla riga 0
            this->map_height = map_height;
            this->map_width = map_width;
            this->map_head = NULL;
            this->map_tail = NULL;

            for(int i=0; i < this->map_height; i++){
                this->newRow();
            }
        }

        /*  
            INFO: 
            PARAMETRI:
            RETURN: 
        */
        void newRow(){
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
            }
        }

        /*  
            INFO: stampa di una "schermata", ovvero di MAP_HEIGHT piani
            PARAMETRI: puntatore alla testa della mappa (row numero 0), posizione giocatore
            RETURN: void    
        */
        void printMap(int top_line){
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
                // non riesco a capire cosa sia questo carattere
                // comunque va aggiunto alla lista delle costanti
                // non lo faccio personalmente perche' non sapendo cosa sia
                // non saprei neanche che nome dare alla costante
                cout << MURO << " " << map->num_row;
                map = map->prev;
            }
        }

        ptr_Map getRow(int n){
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

        void setChar(int x, int y, char c){
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
        int getWidth(){ return this->map_width; }
        int getHeight(){ return this->map_height; }
};

class Player{
    private:
        int x;
        int y;
        Mappa *ptr_mappa;

    public:
        Player(Mappa *m = NULL, int x = 0, int y = 1){
            this->x = x;
            this->y = y;
            this->ptr_mappa = m;
            this->ptr_mappa->setChar(this->x, this->y , '@');
            system("PAUSE");
        }

        bool checkMovement(int direction){
            
            switch(direction){
                case SOPRA:
                    if(this->ptr_mappa->getRow(this->y + 1)->row[this->x] == PIATTAFORMA){
                        return true;
                    }
                break;

                case SOTTO:
                    if(this->ptr_mappa->getRow(this->y - 3)->row[this->x] == PIATTAFORMA && this->y > 2){
                        return true;
                    }
                break;

                case SINISTRA:
                    if(this->ptr_mappa->getRow(this->y -1)->row[this->x -1] == PIATTAFORMA){
                        return true;
                    }
                break;

                case DESTRA:
                    if(this->ptr_mappa->getRow(this->y -1)->row[this->x +1] == PIATTAFORMA){
                        return true;
                    }
                break;

                case SPAZIO:

                break;
            }
            return false;
        }

        void move(int direction){
            if(this->checkMovement(direction) == true){
                switch(direction){
                    case SOPRA:
                        this->ptr_mappa->setChar(this->x, this->y +2, '@');
                        this->ptr_mappa->setChar(this->x, this->y, ' ');
                        this->y += 2;
                    break;

                    case SOTTO:
                        this->ptr_mappa->setChar(this->x, this->y -2, '@');
                        this->ptr_mappa->setChar(this->x, this->y, ' ');
                        this->y -= 2;
                    break;

                    case DESTRA:
                        this->ptr_mappa->setChar(this->x +1, this->y, '@');
                        this->ptr_mappa->setChar(this->x, this->y, ' ');
                        this->x += 1;
                    break;

                    case SINISTRA:
                        this->ptr_mappa->setChar(this->x -1, this->y, '@');
                        this->ptr_mappa->setChar(this->x, this->y, ' ');
                        this->x -= 1;
                    break;

                    case SPAZIO:

                    break;
                }
            }
        }

        int getX(){ return this->x; }
        int getY(){ return this->y; }
};









