#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H
#include <fstream>

char find_char(int column, int line);
void move_cursor(int column, int line);
void hide_cursor(void);
bool is_file_empty(std::ifstream& pFile);
void clearscreen(void);
void color(const int background, const int text);
void printfile(char filename[]);

#include "ExternalFunctions.cpp"
#endif