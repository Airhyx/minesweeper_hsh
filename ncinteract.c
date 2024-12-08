#include <ncurses.h>
#include <stdio.h>
#include "grid.h"
#include "ncmove.h"
#define TOTAL_BOMBS 10
#define HIGHLIGHT_COLOR 1
#define SIZE 10
#define FLAG_COLOR 2

int main() {
    char gridFront[SIZE][SIZE];
    bool flagged[SIZE][SIZE] = {false}; // Track flagged cells

    createGrid(gridFront);

    int cursor_row = SIZE / 2, cursor_col = SIZE / 2; // Cursor starts in the middle

    initialize_ncurses();

    WINDOW *grid_win = create_grid_window(SIZE, SIZE);
    draw_grid(grid_win, SIZE, SIZE, gridFront, cursor_row, cursor_col, flagged);

    while (1) {
    int move = input();

    if (move == 5) { // Handle flagging
        flagged[cursor_row][cursor_col] = !flagged[cursor_row][cursor_col]; // Toggle flag
        draw_grid(grid_win, SIZE, SIZE, gridFront, cursor_row, cursor_col, flagged); // Redraw right after flagging
        continue; // Skip movement logic
    }

    handle_movement(&cursor_row, &cursor_col, SIZE, SIZE, move);
    draw_grid(grid_win, SIZE, SIZE, gridFront, cursor_row, cursor_col, flagged);
}


    cleanup_ncurses(grid_win);
    return 0;
}
