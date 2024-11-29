#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#define SIZE 10

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

void createGrid(char grid[SIZE][SIZE]) {
 

    for(int i = 0; i<SIZE;i++)
        {
            for(int j= 0; j<SIZE; j++)
                {
                    grid[i][j] = '#';
                }
        }
}

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



void highscore(int hours, int minutes, int seconds)
{
    // in Arbeit
}