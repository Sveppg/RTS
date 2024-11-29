#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "processmodel.h"
#include "process.h"
#include "queue.h"

struct pctx ctx;

void handle_sigusr1(int signo) {
    (void)signo; 
    if (ctx.running != NULL) {
        p_block(ctx.running); // RUNNING -> BLOCKED
        q_add(ctx.qblocked, ctx.running);
        ctx.running = NULL;
    }else{
        puts("No running process to block\n");
    }
}

void handle_sigusr2(int signo) {
    (void)signo;
    struct process *p = q_remove(ctx.qblocked);
    if (p != NULL) {
        p_unblock(p); // BLOCKED -> READY
        q_add(ctx.qready, p);
    }else{
        puts("No blocked process to unblock!\n");
    }
}

int main() {
    struct queue qready, qblocked;

    ctx.qready = &qready;
    ctx.qblocked = &qblocked;
    qready.start = qready.end = NULL;
    qblocked.start = qblocked.end = NULL;    
    
    signal(SIGUSR1, handle_sigusr1);    
    signal(SIGUSR2, handle_sigusr2);

// 10 prozesse in die Ready queue
    for (int i = 1; i <= 10; i++) {
        struct process *p = (struct process *)malloc(sizeof(struct process));
        p->p_id = i;
        p->p_state = READY;
        q_add(&qready, p);
    }

    ctx.running = q_remove(&qready);
    if (ctx.running != NULL) {
        p_switch_state(ctx.running, RUNNING); // READY -> RUNNING
    }

    while (1) {
        print(&ctx);// geb die Pid aus
        step(&ctx);//Zustand wechseln
        sleep(1);
    }

    return 0;
}



