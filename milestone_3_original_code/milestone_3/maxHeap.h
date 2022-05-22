#include <stdio.h>

struct maxHeap
{
    int bestScore[5];
    int newScore;
};


typedef struct maxHeap maxHeap;

void initialize_maxHeap(maxHeap heap);
void heapify(int array[], int size, int i);
void swap(int *a, int *b);
void insert(int array[], int newNum);
void deleteRoot(int array[], int num);
void printArray(int array[], int size);
void update_heap(maxHeap heap, int score);
void initialize_save_file(maxHeap heap);
void copy_heap(maxHeap source, maxHeap destination);
