#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h> 

/*
    Berechne Quersumme
*/
int sum_of_digits(char *num){
    int sum = 0;
    if(!num) return -1;
    for(int i = 0; num[i] != '\0'; i++){
        if(!isdigit(num[i])){
            return -1;
        }
        sum += num[i] - '0';
    }
    return sum;
}

/*
    teste Quersumme
*/
void test_sum(){
    printf("Test 1: %d\n", sum_of_digits("1234"));
    printf("Test 3: %d\n", sum_of_digits("5678"));
    printf("Test 3: %d\n", sum_of_digits("not a number"));
}

/*
    lese Zeilen ein
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
    teste Zeilen einlesen    
*/
void test_read(){
    FILE *file = fopen("number.txt", "r");
    if(!file){
        perror("Fehler beim öffnen der Datei!");
        return;
    }
    ssize_t len; 
    char *line;
    while((line = read_line(file, &len)) != NULL){
        printf("Zeilen gelesen: (Zeichen gelesen: %zd) %s\n",len, line);
        free(line);
    }
    fclose(file);
}

/*
    Lese datei ein
*/
char **read_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Datei konnte nicht geöffnet werden!");
        return NULL;
    }
    char **lines = NULL;
    size_t count = 0;
    ssize_t len;
    char *line;

    while ((line = read_line(f, &len))) {
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

/*
    teste lesen der Datei
*/
void test_read_file(){
    char **lines = read_file("number.txt");
    if(!lines) return;
    for(size_t i = 0; lines[i]; i++){
        printf("Zeile %zu: %s\n", i , lines[i]);
        free(lines[i]);
    }
    free(lines);
}

