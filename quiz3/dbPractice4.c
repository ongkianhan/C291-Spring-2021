// Program to calculate the power of given equation - > x^n
// example - 2^10 -> 1024
// Number of errors/bugs = 13

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
 *  dbPractice4, exponent function.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/

#include<stdio.h>

double my_power(double x, double z);                    // 1) changed my_power function to be of double type. 2) Removed char y from the function parameters as it is redundant.

double main()                                              // 2) changed main to return double, since the my_power function returns a double
{
    double x = 2;
    double z = -6;                                             // 3) changed char n to int z

    double return_value_function = my_power(x, z);                              // 4) initialize return_value_function as a double. 5) changed my_power function parameters to x and z according to the function definition
    printf("The power value of %f ^ %f is : %f \n", x,z,return_value_function); // 5) changed %s to %d, since z is an int. 6) removed extra : 7) change %d to %f for printing out the value of variable return_value_function of type double.
    return 0;                                                                                       // 8) changed n to z in the line above accordingly. (moved this line down for better readability
}


//the return value of your func should be x^n result
double my_power(double x, double n) {                               // 9) changed parameters char x and char n to int x and int n.
    if(n == 0)                                                  // 10) changed condition to n == 0. If exponent == 0, any value will of x^n will equal to 1.0.
        return 1.0;
    if(n == 1)
        return n;
    double m = (n>0) ? n : -n;                                      // 11) changed the use of the ? operator to probably define the conditions and if_true:if_false to assign m as a negative integer if n < 0.
    double cur = 0;
    double ans = 1;                                                // 12) initialize ans to be equals to x for further calculation of negative indices. This will be our base since x^-n will give us 1/(x^n).
    while(cur != m) {                                            // 13) changed while loop condition to cur != m
        if ( m < 0)                                            // 14) cur has to converge to m. if m < 0, cur has to decrease to m. if m > 0, cur has to increase to m.
            cur--;
        else
            cur++;
        ans *= x;                                               // 15) multiply ans by x, our base. this will be used at the end to return our desired value.
    }
    //ans += my_power(x, (char)(m-cur));                        // 16) commented this line out as it is redundant
    return (n<0) ? 1.0/ans : ans;
}