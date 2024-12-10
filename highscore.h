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


int calcSeconds(int hours, int minutes, int seconds);
long startTimer();
void stopTimer(long time_1);

int readHighscores(const char *filename, Highscore highscores[]);


void writeHighscores(const char *filename, Highscore highscores[], int count);


void checkHighscore(int new_hours, int new_minutes, int new_seconds);

#endif
