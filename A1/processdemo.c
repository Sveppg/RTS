#include "process.h"

int main() {
    struct process p1 = {1, READY};
    struct process p2 = {2, RUNNING};

    p_print(&p1);
    p_print(&p2);

    // Zustände ändern
    p_switch_state(&p1);
    p_switch_state(&p2);

    p_print(&p1);
    p_print(&p2);

    return 0;
}

