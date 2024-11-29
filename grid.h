#ifndef GRID_H
#define GRID_H
#define SIZE 10
void createGrid(char grid[SIZE][SIZE]);
void showGrid(char grid[SIZE][SIZE]);
void setBombs(char grid[SIZE][SIZE], int totalBombs);
void checkNumbers(char grid[SIZE][SIZE]);
long startTimer();
void stopTimer(long time_1);
void highscore(int hours, int minutes, int seconds);
#endif
