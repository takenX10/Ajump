/*
@ Author: Alex Lorenzato

*/
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
using namespace std;

#define ROW_DIM 12  

struct Map
{
    char row[ROW_DIM];
    Map* prev;
    Map* next;
};
typedef Map* ptr_Map;

void newRow(char row[])
{
    for(int i=0; i<ROW_DIM; i++)
    {
        row[i] = 196;
    }
}

void printRow(char row[])
{
    for(int i=0; i<ROW_DIM; i++)
    {
        cout << row[i];
    }
    cout << endl;
}

/*********************** MAIN ************************/

int main()
{
    ptr_Map map = new Map;
    int life = 10;
    char row[ROW_DIM];

    while(life > 0) 
    {
        newRow(row);
        printRow(row);
        life--;
    }

    return 0;
}

/*
//definizione dei tasti premuti (le lettere considerate sono quelle minuscole)
#define SPACE 32
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
[21:18] LuigiBrosNin >[T☆S☆G]<: void Cursore(bool visible)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infoCursore;
    GetConsoleCursorInfo(output, &infoCursore);
    infoCursore.bVisible = visible;
    SetConsoleCursorInfo(output, &infoCursore);
}
[21:18] LuigiBrosNin >[T☆S☆G]<: char tastoPremuto = _getch();
[21:19] LuigiBrosNin >[T☆S☆G]<: switch (tastoPremuto)
        {
            //movimento a sx
        case KEY_A:
        case 'A':
        case ARROW_LEFT:
[21:22] LuigiBrosNin >[T☆S☆G]<: system("cls");
void Setup(Player p, plat l[]) {
    Clear();
    //prima riga
    cout << (char)201;
    for (int i = 1; i < width; i++)
    {
        cout << (char)205;
    }
    cout << (char)187<<endl;
    //righe centrali + player + piattaforma
    for (int i = 1; i < height ; i++)
    {
        for (int j = 0; j < width+1 ; j++)
        {
            if ((i == p.getY()) && (j == p.getX())) {
                cout << "@";
            }
            else {
                if ((j == 0) || (j == width))
                {
                    cout << (char)186;
                }
                else if (l[i].x[j]=='') cout << "";
                else if (l[i].x[j] == ' ') cout << " ";
                else
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    //riga finale
    cout << (char)200;
    for (int i = 1; i < width; i++)
    {
        cout << (char)205;
    }
    cout << (char)188;
    */