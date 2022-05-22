
// Program to check if the given number is a palindrome
// Number of errors/bugs = 15

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
 *  dbPractice3, palindrome function.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/


#include<stdio.h>
#include<stdbool.h>             // 1) import stdbool.h to use true/false boolean values

bool func(int x);              // 2) changed declaration of function to be of bool type, 3) changed x from char to int type

void main() {
    printf("Please enter an integer to check if it is a palindrome: \n");
    int return_value_function;
    scanf(" %d", &return_value_function); // 3) changed return_value_function from char to int type, included a scan for user input


    //return_value_function = func(return_value_function); // 4) commented out this line as it is redundant
    if (func(return_value_function) == false){  // 5) set if condition to if the output of the func is false, print "It is not a palindrome".
        printf("It is not a palindrome \n");
    }
    else{
        printf("It is a palindrome \n");
    }

    return;                     // 6) changed return to return nothing since it is void type
}


//the return value of your func should be true / false only
bool func(int n)                    // 6) changed function to return bool type. 7) changed function arguments to only include int n.
{
    int given_number = n;           // 8) initialized given_number to be equals to n
    int remainder = 0;
    int temp = 0;                   // 9) initialized int temp variable to 0.
    int exponent = 0;               // 10) initialize exponent of 10 to be 0.


    while( given_number > 0) {          // 11) changed while loop condition to given_number > 0, since if we keep dividing given_number by 10 and given_number = 0, the loop should be terminated.
        remainder = given_number % 10;  // 12) changed remainder to be given_number % 10, to retain integrity of n and to use modulo function instead of division
        given_number = given_number/10; // 13) changed to given_number/10, since  n-= 10 does not reflect a division of 10.
        if ( exponent == 0)             // 14) added in edge cases since we are starting from 10^0 with exponent = 0.
            temp = temp + remainder;
        else
            temp = temp*10 + remainder;
        ++exponent;                     // 15) increase exponent by 1, acting as a loop counter if needed

    }

    if (n != temp)                      // 16) changed the if else statements to return the correct value. If temp != n, palindrome = false. Else, palindrome = true.
    {
        return false;
    }
    else
    {
        return true;
    }
}