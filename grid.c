#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "grid.h"
#define SIZE 10
#define HIGHLIGHT_COLOR 1
#define FLAG_COLOR 2

long startTimer()
{
    time_t time_1;
    time_1 = time(NULL);
    return time_1;
}

void stopTimer(long time_1)
{
    time_t time_2;
    time_2 = time(NULL);
    double elapsed_time = difftime(time_2, time_1);
    //printf("\ntime1 = %ld , time2 = %ld ", time_1, time_2);

    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    

    hours = elapsed_time / 3600;
    minutes= ((int)elapsed_time % 3600) / 60;
    seconds = (int)elapsed_time % 60;
    
    printf("\nVergangene Zeit: %d Stunden %d Minuten %d Sekunden.\n", hours, minutes, seconds);
    setHighscore(hours, minutes, seconds);
}

void createGrid(char grid[SIZE][SIZE]) {
 

    for(int i = 0; i<SIZE;i++)
        {
            for(int j= 0; j<SIZE; j++)
                {
                    grid[i][j] = '#';
                }
        }
}

/*
void showGrid(char grid[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c  ", grid[i][j]);
        }
        printf("\n");
    }
}
*/

void showGrid(char grid[SIZE][SIZE])
{
    clear(); // Clears the screen
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            mvprintw(i, j * 2, "%c", grid[i][j]); // Display grid at specified position
        }
    }
    refresh(); // Updates the screen with the changes
}


void setBombs(char grid[SIZE][SIZE], int totalBombs)
    {
     int bombs = 0;
        srand(time(NULL));
        int x;
        int y;
        while (bombs < totalBombs)
            {
                x = rand() % SIZE;
                y = rand() % SIZE;
                if (grid[x][y] != 'x')
                {
                    grid[x][y] = 'x';
                    bombs++;
                }
            }
    }

void checkNumbers(char grid[SIZE][SIZE])
    {
        int countNum = 0;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                countNum = 0;
                if(grid[i][j] != 'x')
                {
                    if (grid[i - 1][j + 1] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i + 1][j - 1] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i + 1][j + 1] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i - 1][j - 1] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i + 1][j] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i][j + 1] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i - 1][j] == 'x')
                    {
                        countNum++;
                    }
                    if (grid[i][j - 1] == 'x')
                    {
                        countNum++;
                    }
                    grid[i][j] = '0' + countNum;
                }
            }
        }
    }


void draw_grid(WINDOW *win, int rows, int cols, char grid[rows][cols], int cursor_row, int cursor_col, bool flagged[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == cursor_row && j == cursor_col) { // Cursor is currently on this cell
                if (flagged[i][j]) { // Cell is flagged, draw with brackets
                    wattron(win, COLOR_PAIR(FLAG_COLOR));
                    mvwprintw(win, i, j * 3, "[F]");
                    wattroff(win, COLOR_PAIR(FLAG_COLOR));
                } else { // Cursor is hovering over an unflagged field
                    wattron(win, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(win, i, j * 3, "[%c]", grid[i][j]);
                    wattroff(win, COLOR_PAIR(HIGHLIGHT_COLOR));
                }
            } else { // Cursor is not on this cell
                if (flagged[i][j]) { // Draw a plain flag without brackets when the cursor is not here
                    wattron(win, COLOR_PAIR(FLAG_COLOR));
                    mvwprintw(win, i, j * 3, " F ");
                    wattroff(win, COLOR_PAIR(FLAG_COLOR));
                } else { // Normal unhighlighted cells
                    mvwprintw(win, i, j * 3, " %c ", grid[i][j]);
                }
            }
        }
    }
    wrefresh(win); // Ensure the changes are rendered
}




void initialize_ncurses()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(HIGHLIGHT_COLOR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(FLAG_COLOR, COLOR_RED, COLOR_BLACK);

}

WINDOW *create_grid_window(int rows, int cols)
{
    return newwin(rows, cols * 4, 1, 1);
}

void clear_cell(char gridBack[SIZE][SIZE], char gridFront[SIZE][SIZE], int cursor_row, int cursor_col) {
    if (gridBack[cursor_row][cursor_col] == 'x') {
        // Handle bomb logic here
        mvprintw(SIZE + 2, 0, "BOOM! You hit a bomb.");
        refresh();
    } else {
        // Reveal safe number
        gridFront[cursor_row][cursor_col] = gridBack[cursor_row][cursor_col];
    }
}


void flood_fill(char gridBack[SIZE][SIZE], char gridFront[SIZE][SIZE], int row, int col)
{
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return;
    if (gridFront[row][col] != ' ') return; // If already revealed, stop
    gridFront[row][col] = gridBack[row][col];

    if (gridBack[row][col] == '0') {
        // Flood neighboring cells
        flood_fill(gridBack, gridFront, row + 1, col);
        flood_fill(gridBack, gridFront, row - 1, col);
        flood_fill(gridBack, gridFront, row, col + 1);
        flood_fill(gridBack, gridFront, row, col - 1);
    }
}


void cleanup_ncurses(WINDOW *grid_win)
{
    delwin(grid_win);
    endwin();
}