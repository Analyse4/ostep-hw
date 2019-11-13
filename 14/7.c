#include<stdlib.h>
#include<stdio.h>

int
main(int argc, char* argv[]) 
{
    int *arr = (int *)malloc(100);
    arr[11] = 44;
    printf("arr[11]: %d\n", *(arr + 11));
    free(arr + 11);
    return 0;
}