#include "process.h"

int main() {
    struct process p1 = {1, READY};
    struct process p2 = {2, RUNNING};
    struct process p3 = {3, BLOCKED};

    p_print(&p1);
    p_print(&p2);
    p_print(&p3);

    // Zustände ändern
    p_switch_state(&p1, READY);
    p_switch_state(&p2, RUNNING);
    p_switch_state(&p3, BLOCKED);

    p_print(&p1);
    p_print(&p2);
    p_print(&p3);

    return 0;
}

