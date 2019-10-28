#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) {
    int fd = open("./test-2.txt", O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR);
    if (fd < 1) {
        fprintf(stderr, "open file faild");
    }
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork faild\n");
    } else if (rc == 0) {
        printf("child start\n");
        int size = 0;
        char buf[21] = "kkkkkkkkkkkkkkkkkkkk";
        size = write(fd, (void *)buf, sizeof(buf)-1);
        if (size < 0) {
            fprintf(stderr, "[child](pid: %d)wirite file faild", getpid());
        }
        printf("[child](pid: %d) write_len: %d\n", getpid(), size);
    } else {
        printf("parent start\n");
        int size = 0;
        char buf[21] = "jjjjjjjjjjjjjjjjjjjj";
        size = write(fd, (void *)buf, sizeof(buf)-1);
        if (size < 0) {
            fprintf(stderr, "[child](pid: %d)wirite file faild", getpid());
        }
        printf("[parent](pid: %d) write_len:%d\n", getpid(), size);
    }
    return 0;
}