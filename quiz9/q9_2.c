//This program uses a function called CharacterScan to read a char from the user
//The function must take an int pointer as a parameter
//The program should print the char and ascii code for each character the user enters
//The program should only exit when the user enters escape

/*
 * quiz9 second file, C291-Spring-2021
 * Program to scan for the character that the user input and breaks the program if esc is entered.
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/15/2021
 *
 * Please read the comments for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



char CharacterScan(int*);

int main(void){
    int *iPtr = 0;
    int exit = 27;  // changed this to int. it will also work if its a char type, since we are dealing with ASCII input.
    int aCode = 0;  // changed acode to aCode to reflect proper C variable naming

    while(aCode != exit){       // changed while loop condition to whenever aCode != 27, or exit, since escape key = 27
            char c = CharacterScan(iPtr);
            if (c == exit) {         // simplified loop condition to if c == exit, in which exit == 27.
                printf("Exiting the code!\n");
                break;
            } else {
                printf("%c is ASCII code %d.\n", c, c);
            }
        }
}

char CharacterScan(int* iPtr){
    char c;
    printf("Enter a character: \n");
    c = getchar();      // upon looking up the internet, some people recommended getchar() since they mentioned that scanf
    getchar();      // might not be the best solution. Nevertheless, for our simple function, scanf(" %c", &c) also works.
    int a = c;
    iPtr = &a;
    return c;
}