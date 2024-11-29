#ifndef PROCESS_H
#define PROCESS_H

#include <signal.h>

enum state {
    READY,
    RUNNING,
    BLOCKED
};

struct process {
    unsigned int p_id;      
    enum state p_state;     
    struct process *next;   
};

void p_switch_state(struct process *p, enum state new_state);

void print_context();

void handle_sigusr1();

void handle_sigusr2();

void initialize_processes(int num);

#endif
