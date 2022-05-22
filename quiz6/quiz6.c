// Quiz6.c
// median of a sequence
/*
TODO:
The median m of a sequence of n elements is the element that would fall in the middle if the sequence was sorted.
That is, e <= m for half the elements, and m <= e for the others. Clearly, one can obtain the median by sorting
the sequence, but one can do quite a bit better with the following algorithm that finds the kth element of a
sequence between a (inclusive) and b (exclusive). (For the median, use k = n / 2, a = 0, and b = n.)
	select(k, a, b):
	Pick a pivot p in the subsequence between a and b.
	Partition the subsequence elements into three subsequences: the elements <p, =p, >p
	Let n1, n2, n3 be the sizes of each of these subsequences.
	if k < n1
		return select(k, 0, n1).
	else if (k > n1 + n2)
		return select(k, n1 + n2, n).
	else
		return p.
Implement this algorithm and measure how much faster it is for computing the median of a random large sequence,
when compared to sorting the sequence and taking the middle element. Present your observations.
One way to "measure" the time or compare the performance would be to use any of the techniques mentioned at
https://fresh2refresh.com/c-programming/c-time-related-functions/
You may use any approach that you are comfortable with.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int select ( int pos, int a, int b, int array[]);

int select(int pos, int a, int b, int array[])
{

    int pivot = array[(a+b)/2];
    int lessPivot = 0, morePivot = 0, equalPivot = 0;

    for ( int i = a; i < b; i++)
    {
        int temp = array[a];
        if ( temp > pivot)
            morePivot = morePivot + 1;
        else if (temp < pivot)
            lessPivot = lessPivot + 1;
        else
            equalPivot = equalPivot + 1;
    }
    if ( pos < lessPivot) {
            return select(pos, a, lessPivot, array);
    }
    else if (pos > lessPivot+equalPivot)
    {
            return select(pos, lessPivot + equalPivot, b,array);
    }

    else
        return pivot;
}

int sortArray( int array[], int size, int positionOfNumber);

int sortArray(int array[], int size, int positionOfNumber)
{
    int i, current, j;
    for (i = 1; i < size; i++) {
        current = array[i];
        j = i - 1;

        while ( j >= 0 && array[j] > current ) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = current;
    }
    printf("The sorted array is: ");
    for ( i = 0; i < size; i++)
    {
        printf(" %d ", array[i]);
    }
    printf("\n");
    return array[positionOfNumber-1];
}

int main(void)
{
    srand(time(0));
    int size = 10;
    int testArray[size], testArrayTwo[size];
    for ( int i = 0; i < size; i++)
    {
        testArray[i] = rand() % ( 100 - 1 ) + 1;
        testArrayTwo[i] = testArray[i];
    }

    printf("The random sequence of size %d is: ", size);
    for ( int i = 0; i < size; i++)
    {
        printf(" %d ", testArray[i]);
    }
    printf("\n");
    printf("Finding the median of this sequence using select...\n");
    printf("The median of this sequence is: %d\n", select(5, 0, size, testArray));
    printf("Finding the median of this sequence using linearSort...\n");
    printf("The median of this sequence is: %d\n", sortArray(testArrayTwo,size,size/2));


    return 0;
}