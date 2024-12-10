#ifndef NCMOVE_H
#define NCMOVE_H
#include <ncurses.h>

int input();
void displayInput(int direction);
void handle_movement(int *cursor_row, int *cursor_col, int rows, int cols, int move);

#endif