#include <stdio.h>
#include "processmodel.h"

void print(struct pctx *ctx) {
    puts("Laufende Prozesse:");
    if (ctx->running != NULL) {
        p_print(ctx->running);
    } else {
        printf("None\n");
    }
    
    printf("Ready Reihe:\n");
    q_print(ctx->qready);
}

void step(struct pctx *ctx) {
    if (ctx->running != NULL) {
        p_switch_state(ctx->running);
        q_add(ctx->qready, ctx->running);
    }
    ctx->running = q_remove(ctx->qready);
    p_switch_state(ctx->running);
    
}

