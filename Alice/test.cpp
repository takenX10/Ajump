/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<fstream>
#include<string>
#include "../Alessandro/main.cpp"
using namespace std;

int main(){
    /*
    ofstream fp;
    fp.open("testfile.txt");
    string i;
    if(fp.is_open()){
        fp<<"banana33";
    }
    fp.close();
    */
    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    Lista_proiettili proiettili = Lista_proiettili(&m, &p);
    Lista_nemici ent = Lista_nemici(&m, &p, &proiettili);
    Stats(ent.head);
    return 0;
}