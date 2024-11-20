#include "mysignal.h"
#include <stddef.h>

// Setzt alle Bits im Set auf 0 (leeres Set)
void my_sigemptyset(my_sigset_t *set) {
    if (set) {
        *set = 0;
    }
}

// Setzt alle Bits im Set auf 1 (vollständiges Set)
void my_sigfillset(my_sigset_t *set) {
    if (set) {
        *set = ~0U; // Alle 32 Bits auf 1 setzen
    }
}

// Fügt ein Signal (Bit) zum Set hinzu
int my_sigaddset(my_sigset_t *set, int signum) {
    if (!set || signum < 1 || signum > 32) {
        return -1; // Ungültiges Signal
    }
    *set |= (1U << (signum - 1));
    return 0;
}

// Entfernt ein Signal (Bit) aus dem Set
int my_sigdelset(my_sigset_t *set, int signum) {
    if (!set || signum < 1 || signum > 32) {
        return -1; // Ungültiges Signal
    }
    *set &= ~(1U << (signum - 1));
    return 0;
}

// Prüft, ob ein Signal (Bit) im Set enthalten ist
int my_sigismember(const my_sigset_t *set, int signum) {
    if (!set || signum < 1 || signum > 32) {
        return -1; // Ungültiges Signal
    }
    return (*set & (1U << (signum - 1))) != 0;
}
