#include "queue.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>

struct queue qready = {0};
struct queue qblocked = {0};

void enqueue(struct queue *q, struct process *p) {
    p->next = NULL;
    if (!q->tail) {
        q->head = q->tail = p;
    } else {
        q->tail->next = p;
        q->tail = p;
    }
}

struct process *dequeue(struct queue *q) {
    if (!q->head) return NULL;
    struct process *p = q->head;
    q->head = q->head->next;
    if (!q->head) q->tail = NULL;
    return p;
}

void print_queue(const struct queue *q, const char *name){
    printf("%s Queue: \n", name);
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