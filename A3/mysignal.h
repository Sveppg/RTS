#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <stdint.h>

typedef uint32_t my_sigset_t;

void my_sigemptyset(my_sigset_t *set);
void my_sigfillset(my_sigset_t *set);
int my_sigaddset(my_sigset_t *set, int signum);
int my_sigdelset(my_sigset_t *set, int signum);
int my_sigismember(const my_sigset_t *set, int signum);

#endif // MYSIGNAL_H
