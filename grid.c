#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "grid.h"
#define SIZE 10
#define HIGHLIGHT_COLOR 1
#define FLAG_COLOR 2


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
                if (i > 0 && j < SIZE - 1 && grid[i - 1][j + 1] == 'x') countNum++;
                if (i < SIZE - 1 && j > 0 && grid[i + 1][j - 1] == 'x') countNum++;
                if (i < SIZE - 1 && j < SIZE - 1 && grid[i + 1][j + 1] == 'x') countNum++;
                if (i > 0 && j > 0 && grid[i - 1][j - 1] == 'x') countNum++;
                if (i < SIZE - 1 && grid[i + 1][j] == 'x') countNum++;
                if (j < SIZE - 1 && grid[i][j + 1] == 'x') countNum++;
                if (i > 0 && grid[i - 1][j] == 'x') countNum++;
                if (j > 0 && grid[i][j - 1] == 'x') countNum++;
                grid[i][j] = '0' + countNum;
            }
        }
    }
}



void drawGrid(WINDOW *win, int rows, int cols, char gridFront[rows][cols], char gridBack[rows][cols], int cursor_row, int cursor_col, bool flagged[rows][cols]) 
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
    wrefresh(win); // Aktualisiert unser Spielfeld
}





void initializeNcurses()
{
    initscr();        //Initialisiert Fenster
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);    //lässt Pfeil Input zu
    init_pair(HIGHLIGHT_COLOR, COLOR_YELLOW, COLOR_BLACK);    //Farben zu Definitiion zuordnen
    init_pair(FLAG_COLOR, COLOR_RED, COLOR_BLACK);

}

WINDOW *createGridWindow(int rows, int cols)
{
    return newwin(rows, cols * 4, 1, 1);    //ncurses Window Definition
}

void clearCell(char gridFront[SIZE][SIZE], char gridBack[SIZE][SIZE], bool visited[SIZE][SIZE], int row, int col)
{
    // zell versteckt aber keine Bombe? Zeigen
    if (gridFront[row][col] == '#' && gridBack[row][col] != 'x') 
    {
        gridFront[row][col] = gridBack[row][col];

        if (gridBack[row][col] == '0') 
        {
            floodFill(gridFront, gridBack, visited, row, col);
        }
    }
}

void floodFill(char gridFront[SIZE][SIZE], char gridBack[SIZE][SIZE], bool visited[SIZE][SIZE], int row, int col) {
    // Überprüfen ob Zelle auf Spielfeld ist
    if (row < 0 || col < 0 || row >= SIZE || col >= SIZE) return;

    // Return falls schon aufgedeckt und keine '0'
    if (gridFront[row][col] != '#' && gridFront[row][col] != '0') return;

    // Return falls Bombe (Fehler)
    if (gridBack[row][col] == 'x') return;

    // Return falls schon gecleart 
    if (visited[row][col]) return;

    // Zelle als gecleart markieren
    visited[row][col] = true;

    // Clearen
    gridFront[row][col] = gridBack[row][col];

    // Falls Zelle '0' ist, rekursiv um sich selbst floodFill
    if (gridBack[row][col] == '0') 
    { 
        floodFill(gridFront, gridBack, visited, row - 1, col); // Up
        floodFill(gridFront, gridBack, visited, row + 1, col); // Down
        floodFill(gridFront, gridBack, visited, row, col - 1); // Left
        floodFill(gridFront, gridBack, visited, row, col + 1); // Right
        floodFill(gridFront, gridBack, visited, row - 1, col + 1); // Up Right
        floodFill(gridFront, gridBack, visited, row + 1, col + 1); // Down Right
        floodFill(gridFront, gridBack, visited, row - 1, col - 1); // Up Left
        floodFill(gridFront, gridBack, visited, row + 1, col - 1); // Down Right
    }
}



