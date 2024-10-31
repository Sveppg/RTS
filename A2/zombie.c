#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void create_zombie() {
    pid_t pid = fork();

    if (pid == 0) {
        // child dies -> turns to zombie
        exit(0);
    }
}
/*void Usage(char *cmd){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <num of zombies / -1 for all>", cmd);
        return 1;
    }
}*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num of zombies>\n", argv[0]);
        return 1;
    }
    int k = atoi(argv[1]);
    if (k == -1) {
        while (1) {
            create_zombie();
        }
    } else {
        for (int i = 0; i < k; i++) {
            create_zombie();
            usleep(50000);
        }
    }

    puts("Zombies are Alive! check with ps or htop\n");
    sleep(30);

    return 0;
}
