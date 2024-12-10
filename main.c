#include <ncurses.h>
#include <stdio.h>
#include "grid.h"
#include "ncmove.h"
#include "highscore.h"

#define TOTAL_BOMBS 10
#define HIGHLIGHT_COLOR 1
#define SIZE 10
#define FLAG_COLOR 2

void cleanupNcurses(WINDOW *grid_win) 
{
    delwin(grid_win);
    endwin();
}

int main() 
{
    char gridFront[SIZE][SIZE];
    char gridBack[SIZE][SIZE];
    int flagged[SIZE][SIZE] = {0}; 
    bool visited[SIZE][SIZE] = {false}; 
    bool gameWon = false;
    
    createGrid(gridFront);
    setBombs(gridBack, TOTAL_BOMBS); 
    checkNumbers(gridBack);

    int cursor_row = SIZE / 2, cursor_col = SIZE / 2; // Cursor startet mittig

    initializeNcurses();

    WINDOW *grid_win = createGridWindow(SIZE, SIZE);
    drawGrid(grid_win, SIZE, SIZE, gridFront, gridBack, cursor_row, cursor_col, flagged);

    while (1) 
    {
        drawGrid(grid_win, SIZE, SIZE, gridFront, gridBack, cursor_row, cursor_col, flagged); // Grid neu drucken

        int move = input(); 

        if (move == 1 || move == 2 || move == 3 || move == 4) // Input WASD oder Pfeiltasten
        {
            handleMovement(&cursor_row, &cursor_col, SIZE, SIZE, move);
        } else if (move == 5) 
        { 
            if (gridFront[cursor_row][cursor_col] == '#') 
            {
                if(flagged[cursor_row][cursor_col] == 0) flagged[cursor_row][cursor_col] = 1;
                else flagged[cursor_row][cursor_col] = 0; // Toggle Flag
            }
        } else if (move == 6) 
        { 
            if (flagged[cursor_row][cursor_col] == 1) 
            {
                continue; // Zellen mit Flagge nicht clearen
            }
            if (gridBack[cursor_row][cursor_col] == 'x') 
            {
                mvprintw(SIZE + 2, 0, "You hit a bomb! Game over!");
                refresh();
                break; // Game over, falls Bombe bei Clear
            } else 
            {
                clearCell(gridFront, gridBack, visited, cursor_row, cursor_col);
            }
        }
    }

    cleanupNcurses(grid_win);

    if (checkWin(gridBack, flagged, SIZE, SIZE) == 1) gameWon = true;

    if(gameWon == true) 
    {
        printf("GlÅckwunsch");
    } else printf("\n    BOOM! Leider verloren ;/    \n");

    return 0;
}
