#include "alice.h"

using namespace std;
using namespace constants;


// TODO: se hai tempo fixa bug trattini che rimangono in giro 
// TODO: Se la scoreboard e' vuota si bugga a caso.

int main(){
    Classifica lboard = Classifica("Documents\\leaderboard.txt");
    StartScreen(lboard);
    return 0;
}