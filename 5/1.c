// child process will copy content of parent's stack when fork
// parent and child process each have indepandent stack space
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char *argv[]) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork faild\n");
    } else if (rc == 0) {
        printf("[child](pid: %d) x: %d\n", getpid(), x);
    } else {
        x = 200;
        printf("[parent](pid: %d) x: %d\n", getpid(), x);
    }
    return 0;
}