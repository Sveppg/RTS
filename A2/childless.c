#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pwd.h>


void exithandler() {
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        printf("Goodbye, %s\n", pw->pw_name); 
    } else {
        printf("Goodbye, unknown user\n");
    }
}

int main() {
    // Registriere den Exithandler
    /*if (atexit(exithandler) != 0) {
        perror("Fehler beim Registrieren des Exithandlers");
        exit(1);
    }*/

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Kindprozess
        printf("Child started -> PID: %d\nParent-PID -> %d\n", getpid(), getppid());
        sleep(1);
        printf("\nChild died, new Parent-PID: %d\n", getppid());
        puts("\n");
        exit(0);
    } else {
        if (atexit(exithandler) != 0) {
            perror("Fehler beim Registrieren des Exithandlers");
            exit(1);
        }
        // Elternprozess
        printf("Parent started -> terminated instantly, PID: %d\n", getpid());
        exit(0); 
    }
}