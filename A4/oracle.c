#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define BUF_SIZE 512

int is_vowel(char c) {
    char vowels[] = "AEIOUaeiou";
    return strchr(vowels, c) != NULL;
}

void handle_message(const char* message) {
    char pid[10], question[256], response_fifo[20];
    int response_fd;
    char response[256];

    if (sscanf(message, "%9[^:]:%255[^\n]", pid, question) != 2) {
        fprintf(stderr, "Ungültige Nachricht: %s\n", message);
        return;
    }
    snprintf(response_fifo, sizeof(response_fifo), "awnser.%s", pid);

// Give response
    size_t len = strlen(question);
    if (len == 0 || question[len - 1] != '?') {
        snprintf(response, sizeof(response), "Dies ist keine Frage.\n");
    } else if (is_vowel(question[len - 2])) {
        snprintf(response, sizeof(response), "Ja !.\n");
    } else {
        snprintf(response, sizeof(response), "Nein !.\n");
    }

// give answer
    response_fd = open(response_fifo, O_WRONLY);
    if (response_fd == -1) {
        perror("Antwort-FIFO öffnen fehlgeschlagen");
        return;
    }
    write(response_fd, response, strlen(response));
    close(response_fd);
}

int main() {
    const char* ask_fifo = "ask.me";
    char buffer[BUF_SIZE];

// mkfifo in stat.h
    mkfifo(ask_fifo, 0666);

    while (1) {
        int ask_fd = open(ask_fifo, O_RDONLY);
        if (ask_fd == -1) {
            perror("ask.me öffnen fehlgeschlagen");
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_read = read(ask_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // nullstellen entfernen
            handle_message(buffer);
        }

        close(ask_fd);
    }

    unlink(ask_fifo);
    return 0;
}
