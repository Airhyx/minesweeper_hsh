#ifndef GRID_H
#define GRID_H
#define SIZE 10
void createGrid(char grid[SIZE][SIZE]);
void showGrid(char grid[SIZE][SIZE]);
void setBombs(char grid[SIZE][SIZE], int totalBombs);
void checkNumbers(char grid[SIZE][SIZE]);
long startTimer();
void stopTimer(long time_1);
void setHighscore(int hours, int minutes, int seconds);
void draw_grid(WINDOW *win, int rows, int cols, char grid[rows][cols], int cursor_row, int cursor_col, bool flagged[rows][cols]);
void initialize_ncurses();
WINDOW *create_grid_window(int rows, int cols);
void clear_cell(char gridBack[SIZE][SIZE], char gridFront[SIZE][SIZE], int cursor_row, int cursor_col);
void flood_fill(char gridBack[SIZE][SIZE], char gridFront[SIZE][SIZE], int row, int col);
void cleanup_ncurses(WINDOW *grid_win);
#endif