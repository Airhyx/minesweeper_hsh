#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ENTRIES 10
#define MAX_NAME_LEN 50
#define FILENAME "highscores.txt"

typedef struct {
    char name[MAX_NAME_LEN];
    int hours;
    int minutes;
    int seconds;
} Highscore;


int calcSeconds(int hours, int minutes, int seconds) {
    return hours * 3600 + minutes * 60 + seconds;
}


int readHighscores(const char *filename, Highscore highscores[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Highscore-Datei");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %d:%d:%d", highscores[count].name,
                  &highscores[count].hours,
                  &highscores[count].minutes,
                  &highscores[count].seconds) == 4) {
        count++;
        if (count >= MAX_ENTRIES) break;
    }
    fclose(file);
    return count;
}


void writeHighscores(const char *filename, Highscore highscores[], int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Highscore-Datei");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %02d:%02d:%02d\n",
                highscores[i].name,
                highscores[i].hours,
                highscores[i].minutes,
                highscores[i].seconds);
    }
    fclose(file);
}


void checkHighscore(int new_hours, int new_minutes, int new_seconds)
 {
    Highscore highscores[MAX_ENTRIES + 1]; // +1 für möglichen neuen Eintrag
    int count = readHighscores(FILENAME, highscores);

    printf("Aktuelle Highscores:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s %02d:%02d:%02d\n", i + 1,
               highscores[i].name,
               highscores[i].hours,
               highscores[i].minutes,
               highscores[i].seconds);
    }


    int new_total = calcSeconds(new_hours, new_minutes, new_seconds);


    int inserted = 0;
    for (int i = 0; i < count; i++) {
        if (new_total < calcSeconds(highscores[i].hours, highscores[i].minutes, highscores[i].seconds)) {

            for (int j = count; j > i; j--) {
                highscores[j] = highscores[j - 1];
            }

            printf("Neue Highscore-Zeit! Bitte Namen eingeben: ");
            scanf("%s", highscores[i].name);
            highscores[i].hours = new_hours;
            highscores[i].minutes = new_minutes;
            highscores[i].seconds = new_seconds;
            inserted = 1;
            count++;
            break;
        }
    }


    if (!inserted && count < MAX_ENTRIES) {
        printf("Neue Highscore-Zeit! Bitte Namen eingeben: ");
        scanf("%s", highscores[count].name);
        highscores[count].hours = new_hours;
        highscores[count].minutes = new_minutes;
        highscores[count].seconds = new_seconds;
        count++;
    }


    if (count > MAX_ENTRIES) {
        count = MAX_ENTRIES;
    }


    writeHighscores(FILENAME, highscores, count);
    printf("Highscores wurden aktualisiert.\n");
}


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
    checkHighscore(hours, minutes, seconds);
}