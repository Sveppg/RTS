#ifndef PROCESS_H
#define PROCESS_H

#include <signal.h>
#include <stdint.h>

enum state {
    READY,
    RUNNING,
    BLOCKED
};

struct process {
    uint32_t p_id;
    enum state p_state;
    struct process *next;
};

const char *state_str(enum state p_state);
void p_switch_state(struct process *p, enum state new_state);
void p_print(struct process *p);

void p_block(struct process *p);
void p_unblock(struct process *p);

#endif