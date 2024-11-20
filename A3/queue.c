#include "process.h"
#include <stdlib.h>

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
