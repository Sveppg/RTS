#ifndef QUEUE_H
#define QUEUE_H

#include <signal.h>

struct queue {
    struct process *head;   
    struct process *tail;   
};

extern struct queue qready;   
extern struct queue qblocked;

void enqueue(struct queue *q, struct process *p);

struct process *dequeue(struct queue *q);

void print_queue(const struct queue *q, const char *name);

#endif