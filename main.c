#include <stdio.h>
#include "grid.h" 
#include <time.h>
#define SIZE 10


int main()
    {

        int totalBombs = 10;
        char gridBack[SIZE][SIZE];
        char gridFront[SIZE][SIZE];


        long start_time = startTimer();

        createGrid(gridFront);
        showGrid(gridFront);
        setBombs(gridBack, totalBombs);
        printf("\n\n");
        showGrid(gridBack);
        checkNumbers(gridBack);
        printf("\n\n");
        showGrid(gridBack);


        stopTimer(start_time);
        

        return 0;
    }
