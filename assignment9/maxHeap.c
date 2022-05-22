//
// Created by user on 4/30/2021.
//
#include <stdlib.h>
#include <stdio.h>

struct maxHeap
{
    int bestScore;
};


struct maxHeap initializeMaxHeap();


int main (void)
{

    struct maxHeap newHeap;
    newHeap.bestScore = 0;
    printf("This is the best score of the maxHeap: %d",newHeap.bestScore);
    return 0;
}
