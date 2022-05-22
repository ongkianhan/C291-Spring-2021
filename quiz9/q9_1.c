//This program should read a string from the user and print it using a character pointer
//The program is setup to use pointer offset notation to get each character of the string

/*
 * quiz9 first file, C291-Spring-2021
 * Program to get input from user and return the input as output, using a char pointer and fgets()
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/15/2021
 *
 * Please read the comments for more details.
 */

#include <stdio.h>
#include <string.h>

void main(void){
    char s[20];
    char *cPtr;
    cPtr = s;
    printf("Please enter a string less than size of 19 here!\n");
    fgets(s, 19, stdin);  // used fgets() after checking online, and it says there might be security errors using scanf or gets. also restricted to 19 chars, so the last
                            // index in the array can be used for the null character.
    while(*(cPtr) != '\0'){ // changed this to indicate that while *cPtr does not return a value of character '\0'
            printf("%c", *(cPtr++));
    }
    printf("\n");
}