#include<stdlib.h>
#include<stdio.h>

int
main(int argc, char* argv[]) 
{
    int *arr = (int *)malloc(100);
    printf("arr[100]: %d\n", arr[100]);
    free(arr);
    return 0;
}