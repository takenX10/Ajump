/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<fstream>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

struct lista_classifica{
    char nick[30];
    int score;
    struct lista_classifica *next;
};
typedef struct lista_classifica *plista;
class Classifica{
    public:
        plista head;
        const char filename[30] = "leaderboard.txt";
    public:
    
        Classifica(){
            this->head = this->get_file();
        }

    plista get_file(void){
        ifstream OpenFile;
        OpenFile.open(this->filename,ios::in);
        plista Lista = new lista_classifica;
        plista tmp = Lista;
        plista tmp2 = NULL;
        string stringa;
        while (!OpenFile.eof()){
            getline(OpenFile, stringa, '\n');
            strcpy(tmp->nick, stringa.substr(stringa.find(' ')+1, stringa.find(' ', 2)-1).c_str());
            string num = stringa.substr(stringa.find(' ', 2)+1, stringa.find('\n')-1);
            int score = stoi(num);
            
            tmp2 = new lista_classifica;
            tmp->next = tmp2;
            tmp = tmp2;
            tmp->next = NULL;
        }
        OpenFile.close();
        return Lista;
    }
};


int main(){
    Classifica alice = Classifica();
    return 0;
}