#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fehler beim Forken
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Kindprozess
        printf("Child started-> PID: %d\nParent-PID-> %d\n", getpid(), getppid());
        sleep(5);
        printf("\nChild died, new Parent-PID: %d\n", getppid());
        exit(0);
    } else {
        // Elternprozess
        printf("Parent started -> terminated instantly, PID: %d\n", getpid());
        exit(0);  // Elternprozess beendet sich sofort
    }
}
