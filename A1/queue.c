#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"

void q_add(struct queue *q, struct process *p) {
    struct q_node *new_node = (struct q_node *)malloc(sizeof(struct q_node));
    new_node->p = p;
    new_node->next = NULL;

    if (q->end == NULL) {
        q->start = new_node;
    } else {
        q->end->next = new_node;
    }
    q->end = new_node;
}

struct process *q_remove(struct queue *q) {
    if (q->start == NULL) return NULL;

    struct q_node *temp = q->start;
    struct process *p = temp->p;
    q->start = q->start->next;
    if (q->start == NULL) {
        q->end = NULL;
    }

    free(temp);
    return p;
}

void q_print(struct queue *q) {
    struct q_node *current = q->start;
    while (current != NULL) {
        p_print(current->p);
        current = current->next;
    }
}

