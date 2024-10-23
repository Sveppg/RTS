#include <stdlib.h>
#include <unistd.h>
#include "processmodel.h"
#include "process.h"
#include "queue.h"

int main() {
    struct pctx ctx;
    struct queue q;
    ctx.qready = &q;
    q.start = NULL;
    q.end = NULL;

    for (int i = 1; i <= 10; i++) {
        struct process *p = (struct process *)malloc(sizeof(struct process));
        p->p_id = i;
        p->p_state = READY;
        q_add(&q, p);
    }

    ctx.running = q_remove(&q);
    p_switch_state(ctx.running);

    while (1) { // zwei Zustands-Modell
        print(&ctx);
        step(&ctx);
        sleep(1);  //pausiere für 1 Sekunde
    }

    return 0;
}

