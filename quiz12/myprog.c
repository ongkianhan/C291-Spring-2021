/*
 * Quiz11 file 1, C291-Spring-2021
 * Edited source code to print out proper output, created video on debugging process
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/29/2021
 *
 * Please read the comments for more details.
 */


#include <stdio.h>
#define MAX_LETTERS 26

char alphabet[MAX_LETTERS];

void initialize_alphabet(char *a) {
    char *p;
    char current_letter = 'a';
    for (p=a;p<(a+MAX_LETTERS);p++){    //removed extra semicolon on this line
        *p = current_letter++;
    }
}

void reverse_print_alpha(char *b) {
    char *p;                        //removed declaration of static var, and the if statement associated with it
    printf("\nReverse alpha...\n");
    initialize_alphabet(b);
    for (p=(b+MAX_LETTERS-1);p>=b;p--){     //removed extra semicolon here
        printf("%c ",*p);                   //changed this to print p instead of b
    }
    printf("\n");
}

int main(void) {
    int i = 0;                      // instantiated int i = 0;
    while (i++ < 5) {
        reverse_print_alpha(alphabet);
    }
}