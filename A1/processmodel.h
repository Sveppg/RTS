#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include "queue.h"

struct pctx {
    struct queue *qready;
    struct process *running;
};

// Funktionsprototypen
void print(struct pctx *ctx);
void step(struct pctx *ctx);

#endif
