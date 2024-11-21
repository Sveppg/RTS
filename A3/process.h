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

struct queue {
    struct process *head;   
    struct process *tail;   
};

// Funktionen für Warteschlangen
void enqueue(struct queue *q, struct process *p);
struct process *dequeue(struct queue *q);

#endif
