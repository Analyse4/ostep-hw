#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
    int stdout_copy = dup(STDOUT_FILENO);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    int pipefds[2];
    int buf;
    if (pipe(pipefds) == -1) {
        perror("pipe");
        _exit(-1);
    }

    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork faild\n");
        _exit(-1);
    } else if (rc1 == 0) {
        close(STDIN_FILENO);
        //printf("1");
        buf = 4;
        int size = write(STDOUT_FILENO, &buf, 1);
        close(STDOUT_FILENO);
        // resume stdout
        dup2(stdout_copy, STDOUT_FILENO);
        printf("[child1](pid: %d) pipe_write_len: %d\n", getpid(), size);
        _exit(0);
    } else {
        int rc2 = fork();
        if (rc2 < 0)
        {
            fprintf(stderr, "fork faild\n");
            _exit(-1);
        }
        else if (rc2 == 0)
        {
            close(STDOUT_FILENO);
            //int size = scanf("%d", &buf);
            int size = read(STDIN_FILENO, &buf, 1);
            close(STDIN_FILENO);
            // resume stdout
            dup2(stdout_copy, 1);
            printf("[child2](pid: %d) pipe_read_len: %d, pipe_read_data: %d\n", getpid(), size, buf);
            _exit(0);
        }
        else
        {
            int wc = wait(NULL);
            dup2(stdout_copy, 1);
            printf("[parent](pid: %d) run, wc: %d\n", getpid(), wc);
        }       
        int wc = wait(NULL);
        // resume stdout
        dup2(stdout_copy, 1);
        printf("[parent](pid: %d) run, wc: %d\n", getpid(), wc);
    }
    return 0;
}