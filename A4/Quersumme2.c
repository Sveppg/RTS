//----------------

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
    Berechne Quersumme
*/
int sum_of_digits(char *num){
    int sum = 0;
    if(!num || num[0] == '\0') return -1;  // Überprüfen, ob die Eingabe leer ist
    for(int i = 0; num[i] != '\0'; i++){
        if(!isdigit(num[i])){
            return -1;  // Rückgabe von -1, wenn es keine gültige Zahl ist
        }
        sum += num[i] - '0';
    }
    return sum;
}

/*
    Entfernt führende und nachfolgende Leerzeichen und Zeilenumbrüche
*/
void trim(char *str) {
    int start = 0, end = strlen(str) - 1;

    // Entfernen führender Leerzeichen
    while (isspace((unsigned char)str[start])) start++;

    // Entfernen nachfolgender Leerzeichen
    while (end >= start && isspace((unsigned char)str[end])) end--;

    // Verschieben des Strings und Hinzufügen eines Nullterminators
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

/*
    Lese Zeilen ein
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
    Lese Datei ein
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
        trim(line);  // Bereinigen der Zeile
        if (strlen(line) == 0) {  // Überspringen leerer Zeilen
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

/*
    Hauptprogramm
*/
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



#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>


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
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("Teste sum_of_digits:\n");
    test_sum();
    printf("\nTeste read_line:\n");
    test_read();
    printf("\nTeste read_file:\n");
    test_read_file();

    char **lines = read_file(argv[1]);
    if (!lines){
        fprintf(stderr, "Fehler beim Lesen der Datei...\n");
        return EXIT_FAILURE;
    }
    int total_sum = 0;
    for (size_t i = 0; lines[i]; i++) {
        if(lines[i][0] == '\0' || lines[i][0] == '\n'){
            continue;
        }

        int sum = sum_of_digits(lines[i]);
        if (sum == -1) {
            fprintf(stderr, "Ungültige Zeile! %s ignoriert \n", lines[i]);
        }else{
            total_sum += sum;
        }
        free(lines[i]);
    }
    free(lines);

    printf("Summe aller Quersummen: %d\n", total_sum);
    return EXIT_SUCCESS;
}

