#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]); // error handling
        return EXIT_FAILURE;
    }

    char **lines = read_file(argv[1]);
    if (!lines) {
        fprintf(stderr, "Fehler beim Lesen der Datei...\n"); // error handling
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