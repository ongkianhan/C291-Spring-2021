#include <stdio.h>
#include "maxHeap.h"


int size = 0;


void initialize_maxHeap(maxHeap heap)
{
    heap.bestScore[0] = 0;
    heap.bestScore[1] = 0;
    heap.bestScore[2] = 0;
    heap.bestScore[3] = 0;
    heap.bestScore[4] = 0;
    initialize_save_file(heap);
}
void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
void heapify(int array[], int size, int i)
{
    if (size == 1)
    {
        printf("Single element in the heap");
    }
    else
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < size && array[l] > array[largest])
            largest = l;
        if (r < size && array[r] > array[largest])
            largest = r;
        if (largest != i)
        {
            swap(&array[i], &array[largest]);
            heapify(array, size, largest);
        }
    }
}
void insert(int array[], int newNum)
{
    if (size == 0)
    {
        array[0] = newNum;
        size += 1;
    }
    else
    {
        array[size] = newNum;
        size += 1;
        int i;
        for (i = size / 2 - 1; i >= 0; i--)
        {
            heapify(array, size, i);
        }
    }
}
void deleteRoot(int array[], int num)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (num == array[i])
            break;
    }

    swap(&array[i], &array[size - 1]);
    size -= 1;
    for (i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }
}
void printArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

void initialize_save_file(maxHeap heap)
{
    FILE *fp;
    maxHeap *ptr = &heap;
    fp = fopen("./saves/save_best_5.game", "w");
    fwrite(ptr, sizeof(struct maxHeap), 1, fp);

    fclose(fp);
}

void update_heap(maxHeap heap, int score)
{
    FILE *fp;
    fp = fopen("./saves/save_best_5.game", "w");
    int array[6];
    int i,j,a;
    for (i = 0; i < 5; i++)
    {
        array[i] = heap.bestScore[i];
    }
    array[5] = score;
    // arrange according to descending order
    for (i = 0; i < 6; ++i)
    {
        for (j = i + 1; j < 6; ++j)
        {
            if (array[i] < array[j])
            {
                a = array[i];
                array[i] = array[j];
                array[j] = a;
            }
        }
    }

    for (i = 0; i < 5; i++)
    {
        heap.bestScore[i] = array[i];
    }
    fwrite(&heap, sizeof(struct maxHeap), 1,fp);
    fprintf(fp, "\nFrom highest to lowest points:\n");
    for (i = 0; i < 5; i++) {
        fprintf(fp, "\n points: %d\n\n", heap.bestScore[i]);
    }
    fclose(fp);
}

void copy_heap(maxHeap source, maxHeap destination)
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        destination.bestScore[i] = source.bestScore[i];
    }
}