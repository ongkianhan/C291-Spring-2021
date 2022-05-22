//This program includes a struct called car that is used to store information about a given cat
//The program should ask the user for information about their car and initialize a car structure with the given information
//The program should also print the information using a pointer to the initialized struct
//The information printed using the struct and the pointer should be the same

/*
 * Quiz9 file 1, C291-Spring-2021
 * Edited source code to print out proper output
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/21/2021
 *
 * Please read the comments for more details.
 */

#include <stdio.h>
#include <string.h>
// make name a string

struct car{
    char* car;
    int modelYear;
    float speed;
};

int main(void){
    char n[21]; //edited this to 21 since fgets() takes the extra '\n'
    int a;
    float w;

    struct car c, *cPtr = &c; // initialized pointer as struct car

    printf("What is your favorite car's name: \n");
    fgets(n, 20,stdin);       // used fgets() to can input, restricted to 20 characters, including final null
    for ( int i = 0; i < strlen(n); i++)    //remove '\n' from input due to fgets
    {
        if ( n[i] == '\n')
            n[i] = '\0';
    }
    c.car = n;

    printf("When was it launched : \n");
    scanf(" %d", &a);       //changed to %d to take integer values
    c.modelYear = a;

    printf("How much speed does it give: \n");
    scanf("%f", &w);    // changed to %f to take in double values
    c.speed = w;

    // changed respective lines of code to check if pointer information matches with structure information
    printf("Car's name is %s, and should be the same as %s.\n", c.car, cPtr -> car);
    printf("Car's model year is %d, and should be the same as %d.\n", c.modelYear, cPtr -> modelYear);
    printf("Car's speed is %.2f, and should be the same as %.2f.\n", c.speed , cPtr -> speed);
}