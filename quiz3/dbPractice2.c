// Program to count the input characters.
// It reads the input from the keyboard until user hits ENTER
// and then prints it on screen.
// Number of errors/bugs = 13

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
 *  dbPractice2, reading user input function.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/


#include<stdio.h>
int main(void) // 1) changed main from void to int. 2) changed parameter of main function to accept int from void.
{
    int count = 0; // 3) changed count from char type to int type
    char c; // 4) initialized c as a char type
    printf("Please enter your input (with a max of 100 chars), press enter to finish. Enter here: \n");
    scanf("%c", &c);
    putchar(c);                             // reads first character
    while( (c = getchar()) != '\n' && c != EOF) // 5) initialize i as int. 6) changed condition to c != '\0'.
    {
        putchar(c);
                                    // 7) added c = getchar() to update the input
                                    //  8) changed count-- to count++ to increase count as it is being looped
        count++;                    // 9) changed putchar(j) to putchar(c).
    }

    printf("\nnum of chars including spaces: %d", count); // 10) changed \m to \n. 11) changed %s to %d. 12) changed : to ,
    return 0;                                              // 13) changed return 1 to return 0;
}