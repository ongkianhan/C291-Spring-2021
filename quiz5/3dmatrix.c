// Program to read 3-dimensional matrix and display the elements as 1x9 matrix
// Review the slide titled "Memory Organization of Arrays in Ch6" for more details
// TODO
// User may specify any number of rows, columns and depth. Use those to create matrix
// initialize matrix using update_3d method
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
// display cannot use nested loops
// 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 3


void update_3d(double Matrix_3d[][SIZE][SIZE],int sizeI, int sizeJ, int sizeK);
void display_1d(const double Matrix_3d[][SIZE][SIZE], int row, int col, int depth);
int sizeI = 0, sizeJ = 0, sizeK = 0;

int main(void) {
    //prompt the use to enter appropriate dimensions and initialize the matrix accordingly


    printf("Please enter the number of rows for your matrix: ");
    scanf(" %d", &sizeI);
    printf("\n");
    printf("Please enter the number of cols for your matrix: ");
    scanf(" %d", &sizeJ);
    printf("\n");
    printf("Please enter the number of depth for your matrix: ");
    scanf(" %d", &sizeK);
    printf("\n");
    double Matrix_3d[sizeI][sizeJ][sizeK];
    int i = 0, j = 0, k = 0;
    for ( i = 0; i < sizeI; i++){
        for ( j = 0; j < sizeJ; j++){
            for ( k = 0; k < sizeK; k++){
                Matrix_3d[i][j][k] = 0;
            }
        }
    }
    //initialize the array to non-zero values (use scanf or random numbers generator)
    update_3d(Matrix_3d, sizeI, sizeJ, sizeK);
    //display the values
    double *p = &Matrix_3d[0][0][0];
    //display_1d(Matrix_3d, SIZE);
    display_1d(Matrix_3d, sizeI, sizeJ, sizeK);
    return 0;
}

void update_3d(double matrix[][sizeJ][sizeK], int sizeI, int sizeJ, int sizeK) {
    printf("Randomizing the matrix:\n");
    int i = 0;
    srand(time(0));
    for (i = 0; i < sizeI; i++)
    {
        int j = 0;
        for (j = 0; j < sizeJ; j++)
        {
            int k = 0;
            for (k = 0; k < sizeK; k++)
            {
                matrix[i][j][k] = rand() % ( 100 + 1 - 1) + 1;

            }
        }
    }
}


//update as needed. 1 for loop only with 1 iterator to print all values with addresses
//must not be able to update the array.
//Share any observations.
void display_1d(const double matrix[sizeI][sizeJ][sizeK], int row, int col, int depth) {
        const double *p = &matrix[0][0][0];
        int i = 0;
        double pCopy = *p;
        int rowCounter = 0;
        int colCounter = 0;
        for (i = 0; i < row*col*depth; i++) {
            if (( i % (row*col) == 0) && i != row*col){
                printf("[");}
            if ( i == row*col){
                printf("]");
                printf("\n");}
            printf("%p (%0.2f) ", &matrix[0][0][0] + i, *p + i);

    }
}