#include<stdlib.h>
#include<stdio.h>

typedef struct vector
{
    int *arr;
    int len;
    int cap;
}vector;

vector* newVector(int cap)
{
    vector* vec = (vector *)malloc(sizeof(vector));
    if (vec == NULL) {
        perror("Error");
        return NULL;
    }
    vec->arr = (int *)malloc(cap * sizeof(int));
    if (vec->arr == NULL) {
        perror("Error");
        return NULL;
    }
    vec->cap = cap;
    vec->len = 0;
    return vec;
}

int push(vector *vec, int data)
{
    if (vec->len >= vec->cap) {
        vec->arr = realloc(vec->arr, (vec->cap + 10) * sizeof(int));
        if (vec->arr == NULL){
            perror("Error");
            return -1;
        }
        vec->cap += 10;
    }
    vec->arr[vec->len] = data;
    vec->len++;
    return vec->len-1;
}

void show(vector *vec)
{
    printf("[");
    for (int i = 0; i < vec->len; i++) {
        printf("%d ", vec->arr[i]);
    }
    printf("]\n");
}

void release(vector *vec)
{
    free(vec->arr);
    free(vec);
}

int
main(int argc, char *argv[])
{
    vector *vec = newVector(0);
    push(vec, 44);
    push(vec, 444);
    show(vec);
    release(vec);
    return 0;
}