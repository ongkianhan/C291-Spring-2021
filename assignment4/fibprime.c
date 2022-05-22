/*
 *  Followed instructions for question 2 of assignment 4.
 *  Created program to find numbers in the fibonacci sequence that are prime, and printed output accordingly.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/
#include <stdio.h>

int is_prime(int n);

int is_fib_prime(int input);

int testArray[20]; // test array to hold a maximum of 20 fibonacci numbers that are prime



int is_prime(int n)     // checks if user input n is prime
{
    int i = 0;
    if ( n == 1 || n == 2)      // base cases 1 and 2, for simplicity
    {   printf("\nThe number %d is a prime number.\n",n);
        return 1;}
    for (i = 2; i < n + 1; i++)        // starts for loop to check if n is a prime.
    {
        if (n % i == 0)                // If n can be divided by i, we have to check if i == n, since the definition of a
        {                                   // prime number is a number which can only be divided by 1 and itself.
            if (i == n) {
                printf("\nThe number %d is a prime number.\n", n);       // print output and return 1 if number is prime
                return 1;
            }
            else                   // print output and return 0 if number is not prime and returns the lowest divisor
            {   printf("\nThe number %d is not prime. The lowest divisor is %d\n", n,i);
                return 0;}
            }
    }           // end loop
    return 0;
}


int is_fib_prime(int input) // checks if the nth Fibonacci number is prime
{
    int i = 0;
    int start = 0, start2 = 1, final = 0;   // final = Xn+2, start2 = Xn+1, start = Xn
    printf("\n");
    for (i = 3; i < input+1; i++)  // loop logic: Xn+2 = Xn+1 + Xn, start at 3.
    {
        final = start + start2;
        start = start2;
        start2 = final;
        //printf("The %dth Fibonacci number is: %d\n", i,final); <- used for checking if output is correct
    }

    if ( is_prime(final) == 1)  // if else statement to return 1 if fib num is prime, else return 0, and prints output.
    {   printf("The %dth fibonacci number is prime.\n", input);
        return 1;}
    else
    {   printf("The %dth fibonacci number is not prime.\n", input);
        return 0;}
}

int main(void)
{
    int i =0, j = 0, k = 0;
    int testOnePtr = 0, testTwoPtr = 0, testThreePtr = 0;
    int arrayCount = 0;
    for (i = 3; i < 101; i++)           // test loop to populate array for observations
    {
        if (is_fib_prime(i) == 1)
        {
            testArray[arrayCount] = i;
            arrayCount++;
            if (i > 50)
                testThreePtr++;
            else if (i > 10){
            testTwoPtr++;
            testThreePtr++;}
            else {
            testOnePtr++;
            testTwoPtr++;
            testThreePtr++;}
        }
    }
    printf("\nTest run 1: 3 <= n <= 10\n");
    printf("For test one, the prime nth fibonacci numbers are: ");
    for (i = 0; i < testOnePtr; i++ )      // looks at numbers in testArray in which n <= 10
    {
        printf("%d ",testArray[i]);
    }
    printf("\n\n");
    printf("Test run 2: 3 <= n <= 50\n");       // looks at numbers in testArray in which n <= 50
    printf("For test two, the prime nth fibonacci numbers are: ");
    for ( j = 0; j < testTwoPtr; j++ )
    {
        printf("%d ",testArray[j]);
    }
    printf("\n\n");
    printf("Test run 3: 3 <= n <= 100\n");      // looks at numbers in testArray in which n <= 100
    printf("For test three, the prime nth fibonacci numbers are: ");
    for ( k = 0; k < testThreePtr; k++ )
    {
        printf("%d ",testArray[k]);
    }
    printf("\n\n-------End of Test-------");
    return 0;
}