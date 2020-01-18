#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common_threads.h"

//
// Your code goes in the structure and functions below
//

typedef struct __rwlock_t {
    int readers;
    sem_t * lock_semaphore;
    sem_t * rw_w_lock_semaphore;
} rwlock_t;


void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;

    char * lock_semaphore_name = "/lock-semaphore";
    char * rw_w_semaphore_name = "/rw-w-semaphore";

    rw->lock_semaphore = Sem_open(lock_semaphore_name, 1);
    rw->rw_w_lock_semaphore = Sem_open(rw_w_semaphore_name, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    Sem_wait(rw->lock_semaphore);
    rw->readers++;
    if (rw->readers == 1) {
        Sem_wait(rw->rw_w_lock_semaphore);
    }
    Sem_post(rw->lock_semaphore);
}

void rwlock_release_readlock(rwlock_t *rw) {
    Sem_wait(rw->lock_semaphore);
    rw->readers--;
    if (rw->readers == 0) {
        Sem_post(rw->rw_w_lock_semaphore);
    }
    Sem_post(rw->lock_semaphore);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    Sem_wait(rw->rw_w_lock_semaphore);
}

void rwlock_release_writelock(rwlock_t *rw) {
    Sem_post(rw->rw_w_lock_semaphore);
}

//
// Don't change the code below (just use it!)
// 

int loops;
int value = 0;

rwlock_t lock;

void *reader(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
	rwlock_acquire_readlock(&lock);
	printf("read %d\n", value);
	rwlock_release_readlock(&lock);
    }
    return NULL;
}

void *writer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
	rwlock_acquire_writelock(&lock);
	value++;
	printf("write %d\n", value);
	rwlock_release_writelock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);
    loops = atoi(argv[3]);

    pthread_t pr[num_readers], pw[num_writers];

    rwlock_init(&lock);

    printf("begin\n");

    int i;
    for (i = 0; i < num_readers; i++)
	Pthread_create(&pr[i], NULL, reader, NULL);
    for (i = 0; i < num_writers; i++)
	Pthread_create(&pw[i], NULL, writer, NULL);

    for (i = 0; i < num_readers; i++)
	Pthread_join(pr[i], NULL);
    for (i = 0; i < num_writers; i++)
	Pthread_join(pw[i], NULL);

    printf("end: value %d\n", value);

    return 0;
}

