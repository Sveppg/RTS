#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "process.h"
#include "queue.h"

extern struct process *running;

int main() {
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    initialize_processes(10);

    while (1) {
        if (!running) {
            running = dequeue(&qready);
            if (running) {
                p_switch_state(running, RUNNING);
            }
        }

        print_context();
        sleep(2);

        if (running) {
            printf("Process %d finished running.\n", running->p_id);
            free(running);
            running = NULL;
        }
        // if (!qready.head && !qblocked.head && !running) {
        //     printf("All processes completed. Exiting program.\n");
        //     break;        
        // }
    }

    return 0;
}
