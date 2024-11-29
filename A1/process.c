#include <stdio.h>
#include "process.h"

const char *state_str(enum state p_state){
    switch (p_state) {
        case READY:   return "READY";
        case RUNNING: return "RUNNING";
        case BLOCKED: return "BLOCKED";
        default:      return "UNKNOWN";
    }
}

void p_switch_state(struct process *p, enum state new_state) {
    p->p_state = new_state;
}

void p_print(struct process *p) {
    printf("P-ID: %u, Status: %s\n", p->p_id, state_str(p->p_state));
}

void p_block(struct process *p){
    if(p->p_state == RUNNING){
        p->p_state = BLOCKED;
    }
}

void p_unblock(struct process *p){
    if(p->p_state == BLOCKED){
        p->p_state = READY;
    }
}

