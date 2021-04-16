#ifndef PROIETTILI_H
#define PROIETTILI_H

#include<iostream>
#include "funzioni_alex/Mappa.h"
#include "funzioni_alex/Player.h"
#include "funzioni_alex/Alex_constants.hpp"
using namespace constants;
using namespace std;

struct nodo_proiettili{
    int direction;
    int id;
    int x;
    int y;
    struct nodo_proiettili *next;
    struct nodo_proiettili *prev;
};
typedef nodo_proiettili *ptr_nodo_proiettili;

class Lista_proiettili{
    protected:
        ptr_nodo_proiettili head;
        int current_id;
    public:
        Lista_proiettili(void);

        void aggiungi_proiettile(int x, int y, int direction);

        void elimina_proiettile(int id);
        
        void muovi_proiettili(void);
};

#include "Proiettili.cpp"
#endif
