// Fig. E.3: figE_03.c
// The merge sort algorithm using recursion.
// TODO: sortSubArray function uses recursion. Write a new function called sortSubArrayIter which doesn't use recursion
// To implement the new sort function without recursion, where the length of the array is an arbitrary number, 
// Keep merging adjacent regions whose size is a power of 2, and pay special attention to the last area whose size is less.
// Test to make sure that your results are correct.
 
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// function prototypes 
void mergeSort(int array[], size_t length);
void sortSubArray(int array[], size_t low, size_t high);
void sortSubArrayIter(int arr[], size_t size);
void merge(int array[], size_t left, size_t middle1, 
   size_t middle2, size_t right);
void displayElements(int array[], size_t length);
void displaySubArray(int array[], size_t left, size_t right);

int main(void)
{
   int array[SIZE]; // declare the array of ints to be sorted 
    
   srand(time(NULL)); // seed the rand function 
    
   for (size_t i = 0; i < SIZE; i++) {
      array[i] = rand() % 90 + 10; // give each element a value 
   }
        
   puts("Unsorted array:");
   displayElements(array, SIZE); // print the array 
   puts("\n");
   mergeSort(array, SIZE); // merge sort the array 
   puts("Sorted array:");
   displayElements(array, SIZE); // print the array 
} 

// function that merge sorts the array 
void mergeSort(int array[], size_t length)
{
   sortSubArray(array, 0, length - 1);
}

void sortSubArrayIter(int array[], size_t size)
{
    int loop = log2(size);      // Number of times we have to execute the splitting process, which is log2size + 1, if size is not 2^n.
    if ( (loop % 2)  != 0)          // e.g. for size = 10, we have to execute log2(8) + 1 times, which is 3 + 1 = 4 times.
        loop = loop + 1;
    size_t arraySize = size;
    size_t middle = size;
    int count = 2;
    int exponent = 1;
    for ( int i = 0; i < loop; i++)
    {
        if ( middle % 2 != 0)
        {
            size_t middle1 = middle/2 + 1;
            size_t middle2 = middle/2;
        }
        size_t middle = size/2;

        if ( count >= size){
            count = size;}

        for ( int j = 0; j < count; j++)
        {

        }
    }

}

// function that sorts a piece of the array 
void sortSubArray(int array[], size_t low, size_t high)
{
   // test base case: size of array is 1 
   if ((high - low) >= 1) { // if not base case... 
      size_t middle1 = (low + high) / 2;
      size_t middle2 = middle1 + 1;
        
      // output split step 
      printf("%s", "split:   ");
      displaySubArray(array, low, high);
      printf("%s", "\n         ");
      displaySubArray(array, low, middle1);
      printf("%s", "\n         ");
      displaySubArray(array, middle2, high);
      puts("\n");
        
      // split array in half and sort each half recursively 
      sortSubArray(array, low, middle1); // first half 
      sortSubArray(array, middle2, high); // second half 
        
      // merge the two sorted arrays 
      merge(array, low, middle1, middle2, high);
   } 
}

// merge two sorted subarrays into one sorted subarray 
void merge(int array[], size_t left, size_t middle1, 
   size_t middle2, size_t right)
{
   size_t leftIndex = left; // index into left subarray 
   size_t rightIndex = middle2; // index into right subarray 
   size_t combinedIndex = left; // index into temporary array 
   int tempArray[SIZE]; // temporary array 
    
   // output two subarrays before merging 
   printf("%s", "merge:   ");
   displaySubArray(array, left, middle1);
   printf("%s", "\n         ");
   displaySubArray(array, middle2, right);
   puts("");
    
   // merge the subarrays until the end of one is reached 
   while (leftIndex <= middle1 && rightIndex <= right) {
      // place the smaller of the two current elements in result 
      // and move to the next space in the subarray 
      if (array[leftIndex] <= array[rightIndex]) {
         tempArray[combinedIndex++] = array[leftIndex++];
      } 
      else {
         tempArray[combinedIndex++] = array[rightIndex++];
      } 
   }
    
   if (leftIndex == middle2) { // if at end of left subarray ... 
      while (rightIndex <= right) { // copy the right subarray 
         tempArray[combinedIndex++] = array[rightIndex++];
      } 
   } 
   else { // if at end of right subarray... 
      while (leftIndex <= middle1) { // copy the left subarray 
         tempArray[combinedIndex++] = array[leftIndex++];
      } 
   } 
    
   // copy values back into original array 
   for (size_t i = left; i <= right; i++) {
      array[i] = tempArray[i];
   } 
    
   // output merged subarray 
   printf("%s", "         ");
   displaySubArray(array, left, right);
   puts("\n");
} 

// display elements in array 
void displayElements(int array[], size_t length)
{
   displaySubArray(array, 0, length - 1);
} 

// display certain elements in array 
void displaySubArray(int array[], size_t left, size_t right)
{
   // output spaces for alignment 
   for (size_t i = 0; i < left; i++) {
      printf("%s", "   ");
   } 
    
   // output elements left in array 
   for (size_t i = left; i <= right; i++) {
      printf(" %d", array[i]);
   } 
} 