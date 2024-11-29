#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

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
    if (!str || *str == '\0') return;
    char *start = str; // Zeiger auf den Start
    char *end = str + strlen(str) - 1;
    while (*start == ' ' || *start == '\n' || *start == '\t' || *start == '\r') {
        start++;
    }
    while (end >= start && (*end == ' ' || *end == '\n' || *end == '\t' || *end == '\r')) {
        end--;
    }

    size_t len = end - start + 1;
    memmove(str, start, len);
    str[len] = '\0'; 
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

void test(){
    //teste sum
    printf("Test 1: %d\n", sum_of_digits("1234")); // Erwartet: 10
    printf("Test 2: %d\n", sum_of_digits("5678")); // Erwartet: 26
    printf("Test 3: %d\n", sum_of_digits("not a number")); // Erwartet: -1
    //teste read
    FILE *f = fopen("number.txt", "r");
    if (!f) {
        perror("Fehler beim Öffnen der Datei");
        return;
    }

    ssize_t len;
    char *line = read_line(f, &len);
    while (line) {
        printf("Gelesen: %s", line); // Zeile ausgeben
        free(line);
        line = read_line(f, &len);
    }
    fclose(f);
    //test read_file
    char **lines = read_file("number.txt");
    if (!lines) return;

    for (size_t i = 0; lines[i]; i++) {
        printf("Zeile %zu: %s", i, lines[i]);
        free(lines[i]);
    }
    free(lines);
}

int child_sum(char **numbers, int offset, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        int index = offset + i;
        if (numbers[index]) { 
            int partial = sum_of_digits(numbers[index]);
            if (partial != -1) {
                sum += partial;  //errechne summe von allen kindern
            }
        }
    } 
    return sum;
}    

void gen_workers(char **numbers, int pfd[], int n) {
    size_t total_lines = 0;
    while (numbers[total_lines]) total_lines++; // count lines
    
    size_t lines_per_worker = total_lines / n; //lines per child
    size_t remaining_lines = total_lines % n;

    for (int i = 0; i < n; i++) {
        pid_t pid = fork(); // Elternprozess erstellen
        
        if (pid < 0){ 
            perror("Fork fehler...!"); //error handling
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            close(pfd[0]);

            int offset = i * lines_per_worker;
            int count = lines_per_worker + (i == n - 1 ? remaining_lines : 0); 
            int partial_sum = child_sum(numbers, offset, count);
            write(pfd[1], &partial_sum, sizeof(int));
            
            close(pfd[1]);
            exit(0);
        }
    }
    close(pfd[1]); 
}

