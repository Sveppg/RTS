#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char **lines = read_file(argv[1]);
    if (!lines) return EXIT_FAILURE;

    int pfd[2];
    if (pipe(pfd) == -1) {
        perror("Pipe Fehler");
        return EXIT_FAILURE;
    }

    gen_workers(lines, pfd, 5);

    int total_sum = 0;
    for (int i = 0; i < 5; i++) {
        int partial_sum;
        read(pfd[0], &partial_sum, sizeof(int));
        wait(NULL);
        total_sum += partial_sum;
    }
    close(pfd[0]);

    printf("Summe aller Quersummen: %d\n", total_sum);

    for (size_t i = 0; lines[i]; i++) {
        free(lines[i]);
    }
    free(lines);

    return EXIT_SUCCESS;
}
