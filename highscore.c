#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ENTRIES 10
#define SIZE 10
#define MAX_NAME_LEN 50
#define FILENAME "highscores.txt"

typedef struct {
    char name[MAX_NAME_LEN];
    int hours;
    int minutes;
    int seconds;
} Highscore;

int checkWin(char gridBack[SIZE][SIZE], int flagged[SIZE][SIZE], int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // F�r jede '*' muss auch eine 1 bei flagged sein
            if (gridBack[i][j] == '*' && flagged[i][j] != 1) return 0;
            // F�r jede 1 bei flagged aber auch eine '*' bei gridBack
            if (flagged[i][j] == 1 && gridBack[i][j] != '*') return 0; 
        }
    }
    return 1; // Sieg
}

int total_seconds(int hours, int minutes, int seconds) {
    return hours * 3600 + minutes * 60 + seconds;
}

int read_highscores(const char *filename, Highscore highscores[]) {
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

// Funktion zum Schreiben der Highscores in die Datei
void write_highscores(const char *filename, Highscore highscores[], int count) {
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

// Funktion zur Verwaltung des Highscores
void highscore(int new_hours, int new_minutes, int new_seconds) {
    Highscore highscores[MAX_ENTRIES + 1]; // +1 für möglichen neuen Eintrag
    int count = read_highscores(FILENAME, highscores);

    printf("Aktuelle Highscores:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s %02d:%02d:%02d\n", i + 1,
               highscores[i].name,
               highscores[i].hours,
               highscores[i].minutes,
               highscores[i].seconds);
    }

    // Gesamtzeit der neuen Zeit berechnen
    int new_total = total_seconds(new_hours, new_minutes, new_seconds);

    // Prüfen, ob die neue Zeit in die Highscores gehört
    int inserted = 0;
    for (int i = 0; i < count; i++) {
        if (new_total < total_seconds(highscores[i].hours, highscores[i].minutes, highscores[i].seconds)) {
            // Verschieben der bestehenden Einträge, um Platz zu schaffen
            for (int j = count; j > i; j--) {
                highscores[j] = highscores[j - 1];
            }
            // Einfügen des neuen Eintrags
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

    // Wenn die Liste noch nicht voll ist und keine bessere Zeit gefunden wurde
    if (!inserted && count < MAX_ENTRIES) {
        printf("Neue Highscore-Zeit! Bitte Namen eingeben: ");
        scanf("%s", highscores[count].name);
        highscores[count].hours = new_hours;
        highscores[count].minutes = new_minutes;
        highscores[count].seconds = new_seconds;
        count++;
    }

    // Falls es mehr als 10 Einträge gibt, den letzten löschen
    if (count > MAX_ENTRIES) {
        count = MAX_ENTRIES;
    }

    // Highscores speichern
    write_highscores(FILENAME, highscores, count);
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
    highscore(hours, minutes, seconds);
}