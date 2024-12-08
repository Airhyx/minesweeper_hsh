#include <ncurses.h>
#include "ncmove.h"

int main()
{
    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);   //Pfeiltasten zulassen

    int running = 1;

    while (running)
    {
        printw("Press arrow keys, WASD, or F/C to interact. Press ESC to quit.");
        refresh();
        
        int direction = input();
        if (direction == -1) // Exit condition
        {
            running = 0; // Exit the loop
        }
        else
        {
            displayInput(direction);
        }

        refresh();
    }

    // Cleanup ncurses
    endwin();
    return 0;
}