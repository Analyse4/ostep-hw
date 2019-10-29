#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork faild\n");
    } else if (rc == 0) {
        printf("[child](pid: %d) run\n", getpid());
        close(STDOUT_FILENO);
        printf("test");
    } else {
        wait(NULL);
        printf("[parent](pid: %d) run\n", getpid());
    }
    return 0;
}