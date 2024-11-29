#include <stdio.h>
#include "processmodel.h"
#include "process.h"
#include "queue.h"


void print(struct pctx *ctx) {
    puts("Laufende Prozesse:");
    if (ctx->running != NULL) {
        p_print(ctx->running);
    } else {
        puts("Keiner läuft...\n");
    }
    
    puts("\nReady Reihe:\n");
    q_print(ctx->qready, state_str(READY)); // same as L19 

    puts("\nBlocked queue:\n");
    q_print(ctx->qblocked, state_str(BLOCKED)); //state_str for int to char conver
}       

void step(struct pctx *ctx) {

    if (ctx->running != NULL) {
        p_switch_state(ctx->running, READY); // RUNNING -> READY
        q_add(ctx->qready, ctx->running);
    }

    ctx->running = q_remove(ctx->qready);
    if (ctx->running != NULL) {
        p_switch_state(ctx->running, RUNNING); // READY -> RUNNING // no conv nec function dont req
    }else{
        puts("No process in ready queue to run \n");
    }
}
