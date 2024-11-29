#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"


void q_add(struct queue *q, struct process *p) {
    struct q_node *new_node = (struct q_node *)malloc(sizeof(struct q_node));
    if(new_node == NULL){
        fprintf(stderr, "Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_node->p = p;       
    new_node->next = NULL;
    
    if (!q->end) {
        q->start = q->end = new_node;
    } else {
        q->end->next = new_node;
        q->end = new_node;
    }
}

struct process *q_remove(struct queue *q) {
    if (!q->start) return NULL;
    
    struct q_node *temp = q->start;
    struct process *p = temp->p;
    
    q->start = q->start->next;
    if (!q->start){ 
        q->end = NULL;
    }
    free(temp);    
    return p;
}

void q_print(struct queue *q, const char *name) {
    printf("%s Queue: \n", name);
    if (!q->start) {
        printf("Empty\n");
        return;
    }
    struct q_node *current_node = q->start;
    while (current_node) {
        struct process *p = current_node->p;
        printf("%d (%s) \n", p->p_id, 
               (p->p_state == READY) ? "READY" :
               (p->p_state == RUNNING) ? "RUNNING" :
               "BLOCKED");
        current_node = current_node->next;
    }
}

