#include <stdio.h>

/*
 * assignment9 file 2, C291-Spring-2021
 * Calculator Program with 6 functions, as dictated by pdf instructions using array of function pointers
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 04/03/2021
 *
 * Please read the comments for more details.
 */

//declaring functions

double addition_function (int a, int b);
double subtraction_function (int a, int b);
double multiplication_function(int a, int b);
double division_function(int a, int b);
double remainder_function(int a, int b);
double power_function(int base, int exponent); // base^exponent;

double (*function_ptr[6]) (int a, int b);

//defining functions

double addition_function(int a, int b)
{
    return (double) a + b;
}

double subtraction_function( int a, int b)
{
    return (double) a - b;
}

double multiplication_function( int a, int b)
{
    return (double) a * b;
}

double division_function( int a, int b)
{
    return (double) a / b;
}

double remainder_function (int a, int b)
{
    return (double) (a%b);
}

double power_function( int base, int exponent)  // I opted to use a for-loop instead of using the function pow (a,b);
{
    double output = base;
    if ( exponent == 1)
        output = 1;         //edge case, anything to the power of 0 gives you 1
    for ( int i = 0; i < exponent-1; i++)   // since output = base ^ 1, we have to take the range from 0 to exponent - 1
    {
        output*=base;
    }
    return output;
}



int main() {
    char option;
    double result;
    int a, b;
    // defining array of function pointers below
    function_ptr[0] = addition_function;
    function_ptr[1] = subtraction_function;
    function_ptr[2] = multiplication_function;
    function_ptr[3] = division_function;
    function_ptr[4] = remainder_function;
    function_ptr[5] = power_function;

    // do-while loop with switch statement to simulate a calculator program.

    do {
        printf("\n-----Calculator Program-----\nThe calculator can handle 6 functions as shown below\n(1) Addition (+)\n(2) Subtraction(-)"
               "\n(3) Multiplication (*)\n(4) Division (/)\n(5) Remainder (%%)\n(6) Power (^)\nEnter Q or q to "
               "quit\n");

        printf("\nPlease input the operator of your desired function, followed by two integers, a and b:\n");
        scanf(" %c", &option);
        if ( option != 'q' && option != 'Q') {  // if option == q or option == Q, don't scan the 2 ints and just exit the program
            scanf(" %d %d", &a, &b);
        }
            switch (option) {
                case '+':
                    result = (*function_ptr[0])(a, b);
                    printf("Adding %d and %d gives us %.2lf\n", a, b, result);
                    break;
                case '-':
                    result = (*function_ptr[1])(a, b);
                    printf("Subtracting %d by %d gives us %.2lf\n", a, b, result);
                    break;
                case '*':
                    result = (*function_ptr[2])(a, b);
                    printf("Multiplying %d by %d gives us %.2lf\n", a, b, result);
                    break;
                case '/':
                    result = (*function_ptr[3])(a, b);
                    printf("Dividing %d by %d gives us %.2lf\n", a, b, result);
                    break;
                case '%':
                    result = (*function_ptr[4])(a, b);
                    printf("Remainder of %d by %d gives us %.2lf\n", a, b, result);
                    break;
                case '^':
                    result = (*function_ptr[5])(a, b);
                    printf("Power of base %d by exponent %d gives us %.2lf\n", a, b, result);
                    break;

                case 'Q':
                case 'q':
                    printf("Quitting the application... Thanks for using the calculator program!\n");
                    option = 'Q';
                    break;

                default:
                    printf("Option not allowed, please re-enter an appropriate option\n");
                    break;


            }
        } while (option != 'q' && option != 'Q');

    return 0;
}
