#include <stdio.h>
#include "mysignal.h"

int main() {
    my_sigset_t set;
    // leeres Segment
    my_sigemptyset(&set);
    printf("Nach my_sigemptyset: 0x%08X\n", set);

    // segment füllen
    my_sigfillset(&set);
    printf("Nach my_sigfillset: 0x%08X\n", set);

    // add signal 5 
    my_sigaddset(&set, 5);
    printf("Nach my_sigaddset(5): 0x%08X\n", set);

    // del Signal 5
    my_sigdelset(&set, 5);
    printf("Nach my_sigdelset(5): 0x%08X\n", set);

    // schau ob Sig 5 da ist
    int is_member = my_sigismember(&set, 5);
    printf("my_sigismember(5): %d\n", is_member);

    // schau ob signal 1 da ist
    is_member = my_sigismember(&set, 1);
    printf("my_sigismember(1): %d\n", is_member);

    return 0;
}
