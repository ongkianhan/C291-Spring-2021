// The factorial of an integer is the product of the number with all
// the positive integers below it.

// For example: Factorial of 5 = 5 * 4 * 3 * 2 * 1 = 120

// Number of errors/bugs = 7

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
 *  dbPractice1, factorial function.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/

#include<stdio.h>

int factorial(int);

int main(void) {
    int n,fact;
    printf("Debugging Practice 1 - Quiz 3, Q3\n\n");
    printf("Please enter the number whose factorial you wish to find: ");
    scanf(" %d", &n); // 1) changed %f to %d. 2) changed n to &n for scanf
    fact = factorial(n);
    printf("The factorial of %d is %d\n", n, fact); // 3) changed %c to %d to return int fact
}


int factorial(int number) { // 4) changed number from float type to int type
    if ( number == 0) // 5) changed edge case to reflect num == 0 returning 0!, which is 1.
        return 1;
    if ( number == 1)
        return 1;       // 6) changed edge case to reflect num == 1 return 1!, which is 1.
    printf(" %d", number);
    return number * factorial(number - 1); // 7) changed factorial(number+1) to factorial(number - 1) to make sure it converges to 1
}