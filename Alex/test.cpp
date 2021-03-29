#include<iostream>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;
#include <iostream>
#include <windows.h>
#include <conio.h>

namespace constants{
    // Costanti mappa
    constexpr int ROW_DIM = 40;
    constexpr int MAP_HEIGHT = 30;
    constexpr int REFRESH_RATE = 30;     // durata della sleep tra un print e l'altro
    constexpr int CHECKPOINT_ROW = 50;   // frequenza con cui si trova il piano con piattaforma a larghezza ROW_DIM

    // Caratteri
    constexpr char MURO =  177;
    constexpr char PIATTAFORMA = 196;

    // Direzioni
    constexpr int SOPRA = 72;
    constexpr int SOTTO = 80;
    constexpr int DESTRA = 77;
    constexpr int SINISTRA = 75;
    constexpr int SPAZIO = 32;

    // Giocatore
    constexpr int STARTING_X = ROW_DIM/2;
    constexpr int STARTING_Y = 1;
    constexpr int OFFSET = 6;
}

using namespace constants;

char findChar(int column, int line){
    char buf[1];
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, 1, coord, (LPDWORD) &num_read);
    return buf[0];
}

void moveCursor(int column, int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"ERROR! (function: movecursor)"<<endl;
    }
}

void hidecursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

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
        int total_height;

    public:
        Mappa(int map_height = 0, int map_width = 0){
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
        int getTotalHeight(){return this->total_height;}
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
            if(this->ptr_mappa != NULL){
                this->ptr_mappa->setChar(this->x, this->y , '@');
            }
        }

        bool checkMovement(int direction){
            
            switch(direction){
                case SOPRA:
                    if(this->ptr_mappa->getRow(this->y + 1)->row[this->x] == PIATTAFORMA){
                        return true;
                    }
                break;

                case SOTTO:
                    if(this->y > 2){
                        if(this->ptr_mappa->getRow(this->y - 3)->row[this->x] == PIATTAFORMA){
                            return true;
                        }
                    }
                    
                break;

                case SINISTRA:
                    if(this->x-1 >=0){
                        if(this->ptr_mappa->getRow(this->y -1)->row[this->x -1] == PIATTAFORMA){
                            return true;
                        }
                    }
                break;

                case DESTRA:
                    if(this->x+1<this->ptr_mappa->getWidth()){
                        if(this->ptr_mappa->getRow(this->y -1)->row[this->x +1] == PIATTAFORMA){
                            return true;
                        }
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
                        // aggiunta new line 
                        if(OFFSET < this->y && this->y - OFFSET + this->ptr_mappa->getHeight() >  this->ptr_mappa->getTotalHeight()){
                            this->ptr_mappa->newRow();
                            this->ptr_mappa->newRow();
                        }
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

class Gioco{
    private:
        Mappa *mappa_gioco;
        Player *p;

    public:
        Gioco(Mappa *m, Player *p){
            this->mappa_gioco = m;
            this->p = p;
        }
        void auto_print_map(){
            while(true){
                Sleep(REFRESH_RATE);
                this->mappa_gioco->printMap(this->p->getY() + this->mappa_gioco->getHeight() - OFFSET + (OFFSET > this->p->getY() ? OFFSET - this->p->getY() : 0) );
            }
        }
        void keyListener(){
            int key;
            while(true) {
                key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
                this->p->move(key);
            }
        }
};

int main(void){

    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    Gioco  g = Gioco(&m, &p);
    
    hidecursor();                         // per rendere il cursore invisibile

    thread print_map_thread(&Gioco::auto_print_map, g);
    thread get_position(&Gioco::keyListener, g);

    print_map_thread.join();
    get_position.join();    
}