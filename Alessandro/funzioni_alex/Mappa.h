#ifndef MAPPA_H
#define MAPPA_H
#include "Alex_constants.hpp"
using namespace constants;
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
        Mappa(int map_height = 0, int map_width = 0);
        void newRow(void);
        void printMap(int top_line);
        ptr_Map getRow(int n);
        void setChar(int x, int y, char c);
        int getWidth(void);
        int getHeight(void);
        int getTotalHeight(void);
};
#include "Mappa.cpp"
#endif