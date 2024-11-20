#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "process.h"

// Globale Variablen
struct queue qready = {0};
struct queue qblocked = {0};
struct process *running = NULL;

// Funktion zur Änderung des Zustands
void p_switch_state(struct process *p, enum state new_state) {
    printf("Process %d: State changed from %d -> %d\n", p->p_id, p->p_state, new_state);
    p->p_state = new_state;
}

void print_queue(const struct queue *q, const char *name){
    printf("%s Queue: ", name);
    if (!q->head) {
        printf("Empty\n");
        return;
    }
    struct process *current = q->head;
    while (current) {
        printf("%d (%s) \n", current->p_id, 
               (current->p_state == READY) ? "READY" :
               (current->p_state == RUNNING) ? "RUNNING" :
               "BLOCKED");
        current = current->next;
    }
}


// Funktion zur Ausgabe des aktuellen Kontextes
void print_context() {
    print_queue(&qready, "Ready");
    print_queue(&qblocked, "Blocked");
    if (running) {
        printf("Running: Process %d\n", running->p_id);
    } else {
        puts("Running: None\n");
    }

}

// Signalhandler für SIGUSR1
void handle_sigusr1() {
    if (running) {
        printf("SIGUSR1 received: Blocking process %d\n", running->p_id);
        p_switch_state(running, BLOCKED);
        enqueue(&qblocked, running);
        running = NULL;
    }
}

// Signalhandler für SIGUSR2
void handle_sigusr2() {
    struct process *unblocked = dequeue(&qblocked);
    if (unblocked) {
        printf("SIGUSR2 received: Unblocking process %d\n", unblocked->p_id);
        p_switch_state(unblocked, READY);
        enqueue(&qready, unblocked);
    }
}

// Initialisierung der Prozesse
void initialize_processes(int num) {
    for (int i = 1; i <= num; i++) {
        struct process *p = malloc(sizeof(struct process));
        p->p_id = i;
        p->p_state = READY;
        enqueue(&qready, p);
    }
}

int main() {
    // Signalhandler einrichten
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    // Prozesse initialisieren
    initialize_processes(10);

    // Hauptsimulation
    while (1) {
        if (!running) {
            running = dequeue(&qready);
            if (running) {
                p_switch_state(running, RUNNING);
            }
        }

        print_context();
        sleep(2); // Wartezeit für Simulation

        // Simulieren, dass der Prozess fertig ist
        if (running) {
            printf("Process %d finished running.\n", running->p_id);
            free(running);
            running = NULL;
        }
        if (!qready.head && !qblocked.head && !running) {
            printf("All processes completed. Exiting program.\n");
            break;        
        }
    }

    return 0;
}
