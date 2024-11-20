#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <stdint.h>

// Definition eines Signal-Sets mit maximal 32 Signalen
typedef uint32_t my_sigset_t;

// Funktionen zur Manipulation von Signal-Sets
void my_sigemptyset(my_sigset_t *set);
void my_sigfillset(my_sigset_t *set);
int my_sigaddset(my_sigset_t *set, int signum);
int my_sigdelset(my_sigset_t *set, int signum);
int my_sigismember(const my_sigset_t *set, int signum);

#endif // MYSIGNAL_H
