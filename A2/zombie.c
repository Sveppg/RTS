#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void Usage(){
    char UsageMeld[] = "Usage: /zombie Num-of-Zombie processes";
    write(STDERR_FILENO, UsageMeld, sizeof(UsageMeld)-1);
    _exit(EXIT_FAILURE);
}