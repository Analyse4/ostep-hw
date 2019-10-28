#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork faild\n");
    } else if (rc == 0) {
        printf("[child](pid: %d) run\n", getpid());
        int error = execlp("ls", "-l", NULL);
        if (error < 0){
            perror("Error");
        }               
    } else {
        //int wc = wait(NULL);
        //printf("[parent](pid: %d) recycle: %d\n", getpid(), wc);
        printf("[parent](pid: %d) run\n", getpid());
    }
    printf("pid: %d\n", getpid());
    return 0;
}