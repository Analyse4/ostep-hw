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
        // int wc = wait(NULL);
        // printf("[child](pid: %d) run, wc: %d\n", getpid(), wc);
        printf("[child](pid: %d) run\n", getpid());
        // int error = execl("ls", "-l", NULL);
        // perror("Error");
    } else {
        int wc = waitpid(-1, NULL, 0);
        printf("[parent](pid: %d) run, wc: %d\n", getpid(), wc);
    }
    return 0;
}