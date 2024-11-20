#include <stdio.h>
#include "mysignal.h"

int main() {
    my_sigset_t set;

    // Initialisiere das Set als leer
    my_sigemptyset(&set);
    printf("Nach my_sigemptyset: 0x%08X\n", set);

    // Fülle das Set komplett
    my_sigfillset(&set);
    printf("Nach my_sigfillset: 0x%08X\n", set);

    // Füge Signal 5 hinzu
    my_sigaddset(&set, 5);
    printf("Nach my_sigaddset(5): 0x%08X\n", set);

    // Entferne Signal 5
    my_sigdelset(&set, 5);
    printf("Nach my_sigdelset(5): 0x%08X\n", set);

    // Prüfe, ob Signal 5 enthalten ist
    int is_member = my_sigismember(&set, 5);
    printf("my_sigismember(5): %d\n", is_member);

    // Prüfe, ob Signal 1 enthalten ist
    is_member = my_sigismember(&set, 1);
    printf("my_sigismember(1): %d\n", is_member);

    return 0;
}
