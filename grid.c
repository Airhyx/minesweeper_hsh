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
    highscore(hours, minutes, seconds);
}

void createGrid(char grid[SIZE][SIZE]) 
{
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
            if (grid[i][j] != 'x') 
            {
                if (i > 0 && j < SIZE - 1 && grid[i - 1][j + 1] == 'x') 
                {
                    countNum++;
                }
                if (i < SIZE - 1 && j > 0 && grid[i + 1][j - 1] == 'x') 
                {
                    countNum++;
                }
                if (i < SIZE - 1 && j < SIZE - 1 && grid[i + 1][j + 1] == 'x') 
                {
                    countNum++;
                }
                if (i > 0 && j > 0 && grid[i - 1][j - 1] == 'x') 
                {
                    countNum++;
                }
                if (i < SIZE - 1 && grid[i + 1][j] == 'x') 
                {
                    countNum++;
                }
                if (j < SIZE - 1 && grid[i][j + 1] == 'x') 
                {
                    countNum++;
                }
                if (i > 0 && grid[i - 1][j] == 'x') 
                {
                    countNum++;
                }
                if (j > 0 && grid[i][j - 1] == 'x') 
                {
                    countNum++;
                }
                grid[i][j] = '0' + countNum;
            }
        }
    }
}


void highscore(int hours, int minutes, int seconds)
{
    // in Arbeit
}

void draw_grid(WINDOW *win, int rows, int cols, char gridFront[rows][cols], char gridBack[rows][cols], int cursor_row, int cursor_col, bool flagged[rows][cols]) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (i == cursor_row && j == cursor_col) 
            {
                if (flagged[i][j]) 
                {
                    wattron(win, COLOR_PAIR(FLAG_COLOR));
                    mvwprintw(win, i, j * 3, "[F]");
                    wattroff(win, COLOR_PAIR(FLAG_COLOR));
                } else if (gridFront[i][j] == gridBack[i][j]) 
                { 
                    mvwprintw(win, i, j * 3, "[%c]", gridBack[i][j]);
                } else 
                {
                    wattron(win, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(win, i, j * 3, "[%c]", gridFront[i][j]);
                    wattroff(win, COLOR_PAIR(HIGHLIGHT_COLOR));
                }
            } else 
            { 
                if (flagged[i][j]) 
                { 
                    wattron(win, COLOR_PAIR(FLAG_COLOR));
                    mvwprintw(win, i, j * 3, " F ");
                    wattroff(win, COLOR_PAIR(FLAG_COLOR));
                } else if (gridFront[i][j] == gridBack[i][j]) 
                { 
                    mvwprintw(win, i, j * 3, " %c ", gridBack[i][j]);
                } else 
                { 
                    mvwprintw(win, i, j * 3, " %c ", gridFront[i][j]);
                }
            }
        }
    }
    wrefresh(win); // Ensure the grid is updated
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

void clear_cell(char gridFront[SIZE][SIZE], char gridBack[SIZE][SIZE], bool visited[SIZE][SIZE], int row, int col)
{
    // If the cell is hidden and not a bomb, reveal it
    if (gridFront[row][col] == '#' && gridBack[row][col] != 'x') 
    {
        gridFront[row][col] = gridBack[row][col];

        // If the cell is a '0' (no bombs nearby), perform flood fill
        if (gridBack[row][col] == '0') 
        {
            flood_fill(gridFront, gridBack, visited, row, col);
        }
    }
}

void flood_fill(char gridFront[SIZE][SIZE], char gridBack[SIZE][SIZE], bool visited[SIZE][SIZE], int row, int col) {
    // Ensure the cell is in bounds
    if (row < 0 || col < 0 || row >= SIZE || col >= SIZE) return;

    // Stop if it's already revealed or has already been cleared
    if (gridFront[row][col] != '#' && gridFront[row][col] != '0') return;

    // Stop if it's a bomb
    if (gridBack[row][col] == 'x') return;

    // Stop if the cell is already visited
    if (visited[row][col]) return;

    // Mark the cell as visited
    visited[row][col] = true;

    // Reveal the current cell
    gridFront[row][col] = gridBack[row][col];

    // If it's a '0' (no bombs nearby), recursively flood surrounding cells
    if (gridBack[row][col] == '0') 
    { 
        flood_fill(gridFront, gridBack, visited, row - 1, col); // Up
        flood_fill(gridFront, gridBack, visited, row + 1, col); // Down
        flood_fill(gridFront, gridBack, visited, row, col - 1); // Left
        flood_fill(gridFront, gridBack, visited, row, col + 1); // Right
        flood_fill(gridFront, gridBack, visited, row - 1, col + 1); // Up Right
        flood_fill(gridFront, gridBack, visited, row + 1, col + 1); // Down Right
        flood_fill(gridFront, gridBack, visited, row - 1, col - 1); // Up Left
        flood_fill(gridFront, gridBack, visited, row + 1, col - 1); // Down Right
    }
}



