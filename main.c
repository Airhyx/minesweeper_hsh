#include <ncurses.h>
#include <stdio.h>
#include "grid.h"
#include "ncmove.h"

#define TOTAL_BOMBS 10
#define HIGHLIGHT_COLOR 1
#define SIZE 10
#define FLAG_COLOR 2

void cleanup_ncurses(WINDOW *grid_win) {
    delwin(grid_win);
    endwin();
}

int main() {
    char gridFront[SIZE][SIZE];
    char gridBack[SIZE][SIZE];
    bool flagged[SIZE][SIZE] = {false}; // Track flagged cells
    bool visited[SIZE][SIZE] = {false}; //

    createGrid(gridFront);
    setBombs(gridBack, TOTAL_BOMBS); // Set bombs and numbers
    checkNumbers(gridBack);

    int cursor_row = SIZE / 2, cursor_col = SIZE / 2; // Cursor starts in the middle

    initialize_ncurses();

    WINDOW *grid_win = create_grid_window(SIZE, SIZE);
    draw_grid(grid_win, SIZE, SIZE, gridFront, gridBack, cursor_row, cursor_col, flagged);

    while (1) {
        draw_grid(grid_win, SIZE, SIZE, gridFront, gridBack, cursor_row, cursor_col, flagged); // Redraw the grid

        int move = input(); // Get the user input

        if (move == 1 || move == 2 || move == 3 || move == 4) { // Movement keys
            handle_movement(&cursor_row, &cursor_col, SIZE, SIZE, move);
        } else if (move == 5) { // Flag the current cell
            if (gridFront[cursor_row][cursor_col] == '#') {
                flagged[cursor_row][cursor_col] = !flagged[cursor_row][cursor_col];
            }
        } else if (move == 6) { // Clear the current cell
            if (flagged[cursor_row][cursor_col]) {
                continue; // Do not clear flagged cells
            }
            if (gridBack[cursor_row][cursor_col] == 'x') {
                mvprintw(SIZE + 2, 0, "You hit a bomb! Game over!");
                refresh();
                break; // Game over
            } else {
                clear_cell(gridFront, gridBack, visited, cursor_row, cursor_col); // Reveal the cell
            }
        }
    }

    cleanup_ncurses(grid_win);
    return 0;
}
