#ifndef GRID_H
#define GRID_H
#define SIZE 10
void createGrid(char grid[SIZE][SIZE]);
void showGrid(char grid[SIZE][SIZE]);
void setBombs(char grid[SIZE][SIZE], int totalBombs);
void checkNumbers(char grid[SIZE][SIZE]);
void highscore(int hours, int minutes, int seconds);
void drawGrid(WINDOW *win, int rows, int cols, char gridFront[rows][cols], char gridBack[rows][cols], int cursor_row, int cursor_col, bool flagged[rows][cols]);
void initializeNcurses();
WINDOW *createGridWindow(int rows, int cols);
void clearCell(char gridBack[SIZE][SIZE], char gridFront[SIZE][SIZE], bool visited[SIZE][SIZE], int cursor_row, int cursor_col);
void floodFill(char gridBack[SIZE][SIZE], char gridFront[SIZE][SIZE], bool visited[SIZE][SIZE], int row, int col);
void cleanupNcurses(WINDOW *grid_win);
#endif
