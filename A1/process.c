#include <stdio.h>
#include "process.h"

void p_switch_state(struct process *p) {
    if (p->p_state == READY) {
        p->p_state = RUNNING;
    } else {
        p->p_state = READY;
    }
}

void p_print(struct process *p) {
    printf("P-ID: %u, Status: %s\n", p->p_id, 
           (p->p_state == READY) ? "READY" : "RUNNING");
}

