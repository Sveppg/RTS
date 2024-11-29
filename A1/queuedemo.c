#include <stdio.h>
#include <stdlib.h>  
#include "queue.h"
#include "process.h"

int main() {
    struct queue q = {NULL, NULL};  // Initialisiere die Queue

    // Initialisiere zwei Prozesse
    struct process p1 = {1, READY};
    struct process p2 = {2, READY};

    //printf("Prozesse in der Queue: \n");
    q_add(&q, &p1);
    q_add(&q, &p2);

    printf("Inhalt der Queue vor dem Entfernen: \n");
    q_print(&q, state_str(READY));
    q_print(&q, state_str(BLOCKED));



    struct process *removed = q_remove(&q);
    if (removed != NULL) {
        printf("\nEntfernter Prozess: ");
        p_print(removed);
    } else {
        printf("\nKein Prozess wurde entfernt -> leere Queue.\n");
    }

    printf("\nInhalt der Queue nach dem Entfernen eines Prozesses: \n");
    q_print(&q, sta);

    return 0;
}
