#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#define MAX_ENTRIES 10
#define MAX_NAME_LEN 50
#define FILENAME "highscores.txt"


typedef struct {
    char name[MAX_NAME_LEN];
    int hours;
    int minutes;
    int seconds;
} Highscore;

int checkWin(char gridBack[SIZE][SIZE], int flagged[SIZE][SIZE], int rows, int cols);

int total_seconds(int hours, int minutes, int seconds);
long startTimer();
void stopTimer(long time_1);

int read_highscores(const char *filename, Highscore highscores[]);


void write_highscores(const char *filename, Highscore highscores[], int count);


void highscore(int new_hours, int new_minutes, int new_seconds);

#endif
