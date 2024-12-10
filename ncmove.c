#include <ncurses.h>

// Input handling
int input()
{
    int ch = getch(); // Get user input

    switch (ch)
    {
        case KEY_UP:    
        case 'w':       // W key (lowercase) maps to Up
        case 'W':       // W key (uppercase) maps to Up
            return 1;

        case KEY_DOWN:  // Arrow Down
        case 's':       // S key (lowercase) maps to Down
        case 'S':       // S key (uppercase) maps to Down
            return 3;

        case KEY_LEFT:  // Arrow Left
        case 'a':       // A key (lowercase) maps to Left
        case 'A':       // A key (uppercase) maps to Left
            return 2;

        case KEY_RIGHT: // Arrow Right
        case 'd':       // D key (lowercase) maps to Right
        case 'D':       // D key (uppercase) maps to Right
            return 4;

        case 'f':       // Flag set
        case 'F':       
            return 5;

        case 'c':       // Clear field
        case 'C':       
            return 6;

        case 27:        // ASCII representation of ESC key
            return -1; // Exit signal

        default:
            return 0; // Invalid input
    }
}

void displayInput(int direction)
{
    switch (direction)
    {
        case 1:
            printw("\nYou chose: Up\n");
            break;
        case 2:
            printw("\nYou chose: Left\n");
            break;
        case 3:
            printw("\nYou chose: Down\n");
            break;
        case 4:
            printw("\nYou chose: Right\n");
            break;
        case 5:
            printw("\nFlag set!\n");
            break;
        case 6:
            printw("\nField cleared!\n");
            break;
        case 0:
            printw("\nInvalid input!\n");
            break;
    }
    refresh();
}

void handle_movement(int *cursor_row, int *cursor_col, int rows, int cols, int move) 
{
    if (move == 1 && *cursor_row > 0) { // Move up
        (*cursor_row)--;
    } else if (move == 3 && *cursor_row < rows - 1) { // Move down
        (*cursor_row)++;
    } else if (move == 2 && *cursor_col > 0) { // Move left
        (*cursor_col)--;
    } else if (move == 4 && *cursor_col < cols - 1) { // Move right
        (*cursor_col)++;
    }
}
