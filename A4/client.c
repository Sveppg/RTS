#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Verwendung: %s Stelle eine Frage\n", argv[0]);  //error handling
        return EXIT_FAILURE;
    }

    const char *question = argv[1];
    char ask_fifo[] = "ask.me";
    char response_fifo[20];
    char message[512];
    char response[256];
    int pid = getpid();

// response von fifo
    snprintf(response_fifo, sizeof(response_fifo), "awnser.%d", pid);
    mkfifo(response_fifo, 0666);

// create message to pid
    snprintf(message, sizeof(message), "%d:%s", pid, question);

    int ask_fd = open(ask_fifo, O_WRONLY);
    if (ask_fd == -1) {
        perror("ask.me öffnen fehlgeschlagen");
        unlink(response_fifo);
        return EXIT_FAILURE;
    }
    write(ask_fd, message, strlen(message));
    close(ask_fd);


    int response_fd = open(response_fifo, O_RDONLY);
    if (response_fd == -1) {
        perror("Antwort-FIFO öffnen fehlgeschlagen");
        unlink(response_fifo);
        return EXIT_FAILURE;
    }
    ssize_t bytes_read = read(response_fd, response, sizeof(response) - 1);
    if (bytes_read > 0) {
        response[bytes_read] = '\0'; // Nullterminierung
        printf("Antwort: %s", response);
    }
    close(response_fd);

/*
    fifo schließen und verbindung trennen    
*/
    unlink(response_fifo);
    return EXIT_SUCCESS;
}
