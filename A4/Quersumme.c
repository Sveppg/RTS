#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
*   Berechne Quersumme
*/
int sum_of_digits(char *num){
    int sum = 0;
    if(!num || num[0] == '\0') return -1; // error handling
    for(int i = 0; num[i] != '\0'; i++){
        if(!isdigit(num[i])){
            return -1;  
        }
        sum += num[i] - '0';
    }
    return sum;
}

/*
*   Entfernt führende und nachfolgende Leerzeichen und Zeilenumbrüche
*/
void trim(char *str) {
    int start = 0, end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) start++;

    while (end >= start && isspace((unsigned char)str[end])) end--;

    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

/*
*   Lese Zeilen ein
*/
char *read_line(FILE *f, ssize_t *len){
    char *line = NULL;
    size_t buffer_size = 0;
    ssize_t read_len = getline(&line, &buffer_size, f);
    if(read_len == -1){
        free(line);
        return NULL;
    }
    if(len){
        *len = read_len;
    }
    return line;
}

/*
*   Lese Datei ein
*/
char **read_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Datei konnte nicht geöffnet werden!"); // error handling
        return NULL;
    }
    char **lines = NULL;
    size_t count = 0;
    ssize_t len;
    char *line;

    while ((line = read_line(f, &len))) {
        trim(line); 
        if (strlen(line) == 0) {
            free(line);
            continue;
        }
        char **temp = realloc(lines, (count + 1) * sizeof(char *));
        if (!temp) {
            perror("Speicherzuweisung fehlgeschlagen!");
            free(line);
            for (size_t i = 0; i < count; i++) free(lines[i]);
            free(lines);
            fclose(f);
            return NULL;
        }
        lines = temp;
        lines[count++] = line;
    }
    fclose(f);
    lines = realloc(lines, (count + 1) * sizeof(char *));
    if (!lines) {
        perror("Speicherzuweisung fehlgeschlagen!");
        return NULL;
    }
    lines[count] = NULL;
    return lines;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char **lines = read_file(argv[1]);
    if (!lines) {
        fprintf(stderr, "Fehler beim Lesen der Datei...\n");
        return EXIT_FAILURE;
    }

    int total_sum = 0;
    for (size_t i = 0; lines[i]; i++) {
        int sum = sum_of_digits(lines[i]);
        if (sum != -1) {
            total_sum += sum;
        } else {
            fprintf(stderr, "Ungültige Zeile ignoriert: %s\n", lines[i]);
        }
        free(lines[i]);
    }
    free(lines);

    printf("Summe aller Quersummen: %d\n", total_sum);
    return EXIT_SUCCESS;
}