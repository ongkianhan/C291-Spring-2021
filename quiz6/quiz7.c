
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


#define SIZE 5

bool mySwap (int* x, int* y);

bool mySwap( int* x, int*y)
{
    bool output = 0;

    return output;
}

int main(void)
{
    short numbers[SIZE] = { 1, 2, 3, 4, 5};
    int i = 0;
    short* nPtr = numbers;

    for ( i = 0; i < SIZE; i++)
    {
        printf("%hd ", nPtr[i]);
    }


    return 0;
}