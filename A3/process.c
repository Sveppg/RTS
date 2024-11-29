#include "process.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct process *running = NULL;

void p_switch_state(struct process *p, enum state new_state) {
    printf("Process %d: State changed from %d -> %d\n", p->p_id, p->p_state, new_state);
    p->p_state = new_state;
}

void print_context() {
    print_queue(&qready, "Ready");
    print_queue(&qblocked, "Blocked");
    if (running) {
        printf("Running: Process %d\n", running->p_id);
    } else {
        puts("Running: None\n");
    }
}

//SIGUSR1
void handle_sigusr1() {
    if (running) {
        printf("SIGUSR1 received: Blocking process %d\n", running->p_id);
        p_switch_state(running, BLOCKED);
        enqueue(&qblocked, running);
        running = NULL;
    }
}

//SIGUSR2
void handle_sigusr2() {
    struct process *unblocked = dequeue(&qblocked);
    if (unblocked) {
        printf("SIGUSR2 received: Unblocking process %d\n", unblocked->p_id);
        p_switch_state(unblocked, READY);
        enqueue(&qready, unblocked);
    }
}

void initialize_processes(int num) {
    for (int i = 1; i <= num; i++) {
        struct process *p = malloc(sizeof(struct process));
        p->p_id = i;
        p->p_state = READY;
        enqueue(&qready, p);
    }
}
