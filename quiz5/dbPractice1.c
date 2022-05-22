// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and make sure program works as intended.
// for each bug fix, add a comments specifying what you fixed.
// Number of errors/bugs = 12

/*
 * Fixed bugs for dbPractice1.c for quiz5.
 * Created program to read integers into a 3x3 matrix and display them correctly.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/


#include <stdio.h>
void display(int Matrix[3][3],int size);

int main(void) {
    int size = 3;
    int Matrix[size][size]; // 1. Matrix size shouldn't be size - 1, it should be size, for a 3x3 matrix
    printf("Enter 9 elements of the matrix:\n");
    int i = 0;              // 2. int i = 0; as a declaration, not just int i
    for (i = 0; i < size; i++)      //3. for loop has to be separated by ; not ,
    {
        int j = 0;
        for (j = 0; j < size; j++){      // 4. j = 0; as first condition in the for loop in this case should be blank
            scanf("%d", &Matrix[i][j]);     //5. change %f to %d since we are using integers.  6. change colon at the end of statement to semi colon
        }
    }
    display(Matrix,3);                 // 7. change &Matrix to Matrix, since we are referencing the entire matrix in the subsequent function, not just the address
    return 0;
}

void display(int Matrix[3][3], int size) {   // 8. change matrix attribute to int instead of float since all Matrix type objects in this case are ints 9. change attribute of size from char to int
    int i = 0;                          // 10. Not necessarily a bug, but I moved the initialization for j and i outside the for loop conditions just incase there were some errors with the C99 version and the linux version
    for ( i = 0; i < size; i++) {
        int j = 0;
        for (j = 0; j < size; j++)     //11. changed for loop to for ( j = 0; j < size; j++) to print correct output. In the original version of for (int j = size; j >= 0; j--), it will print the reverse of what we wanted.
        {                                               // i.e. for (int j = size; j >= 0; j--) will print [2], [1], [0], but we want [0], [1],[2] since this is a 2d array.
            printf("%d ", Matrix[i][j]);        // 12. changed what we want to print to Matrix[i][j] 13. removed the comma because it looks weird and makes it not look like a matrix
        }
        printf("\n");
    }

}