#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_
//lista colori:
#define Blue 1
#define Green 2
#define Aqua 3
#define Red 4
#define Purple 5
#define Yellow 6
#define White 7
#define Gray 8
#define Light_Blue 9
#define Black 0
#define Light_Green 10
#define Light_Aqua 11
#define Light_Red 12
#define Light_Purple 13
#define Light_Yellow 14
#define Bright_White 15

void clearscreen(void);
void color(const int background, const int text);
void printfile(char filename[]);

#include "screen_manager.cpp"
#endif