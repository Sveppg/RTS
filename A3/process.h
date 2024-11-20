#ifndef PROCESS_H
#define PROCESS_H

#include <signal.h>

enum state {
    READY,
    RUNNING,
    BLOCKED
};

struct process {
    unsigned int p_id;      // Prozess-ID
    enum state p_state;     // Zustand des Prozesses
    struct process *next;   // Nächster Prozess in einer Warteschlange
};

struct queue {
    struct process *head;   // Kopf der Warteschlange
    struct process *tail;   // Ende der Warteschlange
};

// Funktionen für Warteschlangen
void enqueue(struct queue *q, struct process *p);
struct process *dequeue(struct queue *q);

#endif // PROCESS_H
