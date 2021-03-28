/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include <ncurses.h>
using namespace std;

struct listaNemici{
    class Enemy nemico;
    struct listaNemici *next;
};

typedef struct listaNemici* plistaNemici;

struct position{
    int x;
    int y;
};

// Funzione che si occupa di rimuovere un nemico dalla lista dei nemici
plistaNemici death(plistaNemici list, int id){
    plistaNemici aux = list;
    plistaNemici prev = NULL;
    while(aux->nemico.id != id && aux != NULL){
        prev = aux;
        aux = aux->next;
    }
    if(prev == NULL){ // l'elemento da eliminare e' il primo
        list = list->next;
        delete(aux);
    }else if(aux != NULL){
        prev->next = aux->next;
        delete(aux);
    }
    return list;
}

// Funzione che si occupa di generare un nuovo id valido per la classe
// L'id corrente viene passato per riferimento
int newid(int &id_backup){
    id_backup++;
    return id_backup;
}


// Funzione che si occupa di pulire la lista dei nemici
// Da chiamare alla fine di ogni partita

plistaNemici pulisci_lista_nemici(plistaNemici head){ //perchè non void (?)
    plistaNemici aux = head;
    while(head != NULL){
        aux = aux->next;
        delete(head);
        head = aux;
    }
    return head;
}

/****** Manca roba da implementare *************/
//funzione che si occupa di far "spawnare un nemico"
plistaNemici spawn(plistaNemici *head, int &id_backup, int vita, int danno, int tipo){
    plistaNemici aux = new struct listaNemici;
    int id = newid(id_backup);
    position pos;
    // dobbiamo calcolare la posizione in cui farlo spawnare, attendiamo la mappa di alex
    aux->nemico.setStats(vita, danno, pos, id);
}

class Entity{ // classe madre
protected:

public:
    int vita;
    int danno;
    int id;
    position posEntity;
    Entity(position pos, int vita = 0, int danno = 0, int id=0){
        this->vita = vita;
        this->danno = danno;
        this->posEntity.x = pos.x;
        this->posEntity.x = pos.y;
        this->id = id;
    }
    // presuppone che il movimento sia possibile
    bool move(position newPos){
        this->posEntity.x = newPos.x;
        this->posEntity.y = newPos.y;
    }

    void setStats(int vita, int danno, position pos, int id){
        this->vita = vita;
        this->danno = danno;
        this->posEntity = pos;
        this->id = id;
    }
};

class Enemy: public Entity{
protected:
    char type;
    char boss;
public:


};

class Player: public Entity{

};


//in attesa della mappa di Alessio
position calcola_movimento_nemico(class Enemy c, struct mappa *head){
    position pos;

    c.move(pos);
    return pos;
}

position calcola_movimento_player(class Player c, struct mappa *head){
    position pos;

    return pos;
}