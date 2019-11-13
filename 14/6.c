#include<stdlib.h>
#include<stdio.h>

int
main(int argc, char* argv[]) 
{
    int *arr = (int *)malloc(100);
    arr[5] = 44;
    free(arr);
    printf("arr[5]: %d\n", arr[5]);
    return 0;
}