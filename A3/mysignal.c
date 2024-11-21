#include "mysignal.h"
#include <stddef.h>

//all bits to 0
void my_sigemptyset(my_sigset_t *set) {
    if (set) {
        *set = 0;
    }
}

// all bits to 1
void my_sigfillset(my_sigset_t *set) {
    if (set) {
        *set = ~0U; // Alle 32 Bits auf 1 setzen
    }
}

int my_sigaddset(my_sigset_t *set, int signum) {
    if (!set || signum < 1 || signum > 32) {
        return -1; // Ungültiges Signal
    }
    *set |= (1U << (signum - 1));
    return 0;
}

int my_sigdelset(my_sigset_t *set, int signum) {
    if (!set || signum < 1 || signum > 32) {
        return -1; // Ungültiges Signal
    }
    *set &= ~(1U << (signum - 1));
    return 0;
}

//see if bit is in seg
int my_sigismember(const my_sigset_t *set, int signum) {
    if (!set || signum < 1 || signum > 32) {
        return -1; // Ungültiges Signal
    }
    return (*set & (1U << (signum - 1))) != 0;
}
