#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t n = 0; // Anzahl der aktiven Kindprozesse

// Signalhandler für SIGCHLD
void sigchld_handler() {
    int status;
    pid_t pid;

    // Warten auf beendete Kindprozesse
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        n--; // Decrementiere die Anzahl der Kindprozesse
        if (WIFEXITED(status)) {
            printf("Child %d: terminated with status %d (n=%d)\n", pid, WEXITSTATUS(status), n);
        } else if (WIFSIGNALED(status)) {
            printf("Child %d: terminated by signal %d (n=%d)\n", pid, WTERMSIG(status), n);
        } else {
            printf("Child %d: terminated abnormally (n=%d)\n", pid, n);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_children>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int k = atoi(argv[1]);
    if (k <= 0) {
        fprintf(stderr, "Number of children must be positive.\n");
        return EXIT_FAILURE;
    }

    // Signalhandler einrichten
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    // Kindprozesse erzeugen
    for (int i = 0; i < k; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0) {
            // Kindprozess
            printf("Child %d: started (n=%d)\n", getpid(), n);
            sleep(2); // Kindprozess simuliert Arbeit
            printf("Child %d: exiting (n=%d)\n", getpid(), n);
            exit(0);
        } else {
            // Elternprozess
            n++;
            printf("Parent %d: Child %d started (n=%d)\n", getpid(), pid, n);
        }
    }

    // Elternprozess wartet, bis n == 0
    while (n > 0) {
        pause(); // Warten auf ein Signal
    }

    printf("All child processes have exited. Parent exiting (n=%d).\n", n);
    return EXIT_SUCCESS;
}
