#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS 26

char alphabet[MAX_LETTERS];

void initialize_alphabet(char *a) {
    char *p;
    p = (char*) malloc(sizeof(char) * 26);
    int i;
    char current_letter = 'a';
    for (i = 0 ; i <MAX_LETTERS;i++){
        *(p+i) = current_letter + i;
    }
    strcpy(a,p);
    free(p);
}

void reverse_print_alpha(char *b) {
    int i;
    printf("\nReverse alpha...\n");
    initialize_alphabet(b);
    for (i = MAX_LETTERS-1;i >= 0;i--)
    {
        printf("%c ",*(b+i));
    }
    printf("\n");
}

int main(void) {
    int i = 0;
    while (i++ < 5) {
        reverse_print_alpha(alphabet);
    }
}
