//This program allocated memory for an NxM integer array dynamically
//The program then prints the 2D array in a matrix form using a combination of * and [] operators
//Note: You can't use ** or [][] for printing the values (use a combination of * and [] only.

/*
 * quiz9 third file, C291-Spring-2021
 * Program to initialize a 3X5 2D matrix dynamically, and then print out the contents of the 2D array and free the pointers.
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/15/2021
 *
 * Please read the comments for more details.
 */

#include <stdio.h>
#include <stdlib.h>
int main() {
    int N = 3, M = 5;
    int i, j;
    int**d_array = (int**) malloc( N * sizeof(int*) ); 	//Allocating memory for 2D array (N rows)
    for(i=0; i< N; i++)
        d_array[i] = (int*) malloc(M * sizeof(int*) );  //Allocating memory for each row with M columns)
    //Initializing 2D array using [ ][ ] notation
    printf("Initializing array values!\n");
    for(i=0; i< N; i++) {
        for(j=0; j < M; j++) {
            *(d_array[i]+j) = i+j; // 1. changed this to use a combination of * and []. also, added semi colon in.
        }
    }
    //Accessing 2D array using a combination of * and [] notation
    printf("\n");
    for(i=0; i< N; i++) {
        for(j=0; j < M; j++) {
            printf("%d ",*(d_array[i]+j)); // 2. changed this to use a combination of * and []. also, changed it from
        }                                  // d_array[j] + i to d_array[i] + j to get intended output.
        printf("\n");
    }

    //Deallocating 2D array
    for(i=0; i< N; i++)
        free(d_array[i]);               //3. changed this to free(d_array[i]). free( *(d_array+i)) also works in this case.
    free(d_array);
}