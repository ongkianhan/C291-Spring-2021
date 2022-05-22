#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*
 * Assignment 7, C291-Spring-2021
 * Answered questions accordingly and created functions
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/20/2021
 *
 * Please read the comments for more details.
 */
void functionOne();

char* functionTwo( char* userInput);
char* functionThree( char* double_integer_string);

char* functionThree(char* input)
{
    int sumInt = 0, count = 0;
    double sumDouble = 0;
    int inputLength = strlen(input);
    char* stringCopy = (char*) malloc((inputLength + 1) * sizeof(char));
    strcpy(stringCopy, input);
    char* startOfNumber = stringCopy, *endOfNumber = stringCopy; // used to locate a number in the string, but doesn't confirm if its a double or integer.
    // extract doubles and integers
    while (*stringCopy != '\0')
    {

        while (isdigit(*startOfNumber) == 0 && *startOfNumber != '\0')
        {
            startOfNumber++;
            endOfNumber++;
            stringCopy++;
            if ( strlen(stringCopy) == 0)
                break;
        }
        if ( strlen(stringCopy) == 0 )
            break;
        if ( isdigit(*startOfNumber) >= 1)
        {
            while ( isdigit(*endOfNumber) > 0 || *endOfNumber == '.' && isdigit(*(endOfNumber+1)) != 0 && *endOfNumber != '\0')
            {
                endOfNumber++;
                count++;
            }
        }
        char* thisNumber = (char*) malloc((count)*sizeof(char)); //indicates the string of numbers and decimal point and '\0'
        thisNumber = strncpy(thisNumber, startOfNumber, count);
        char* thisNumberPtr = 0;
        thisNumberPtr = strchr(thisNumber, 46);
        if ( thisNumberPtr != 0) // contains a decimal point '.', meaning its a double
        {
            sumDouble += strtod(thisNumber, &thisNumberPtr);
        }
        else
        {
            sumInt += strtol(thisNumber, &thisNumberPtr, 10);
        }
        startOfNumber = endOfNumber + 1;
        endOfNumber++;
        free(thisNumber);
        count = 0;
        stringCopy = endOfNumber;
    }
    int lengthInt = 0, lengthDouble = 0, sumIntCpy = sumInt, sumDoubleCpy = sumDouble;
    while ( sumIntCpy / 10 != 0)
    {
        lengthInt++;
        sumIntCpy/=10;
    }
    while ( sumDoubleCpy / 10 >= 1)
    {
        lengthDouble++;
        sumDoubleCpy/=10;
    }
    // word count for "The sum of all integers is....... doubles ..... YYYY.YY" without numbers is 57.
    char* finalOutputInt = (char*) malloc((30+1+lengthInt) * sizeof(char)); //30
    char* finalOutputDouble = (char*) malloc((27+1+lengthDouble+3) * sizeof(char)); //27, lengthDouble + 3 since we are formatting double to 2 dp with 1 decimal point
    snprintf(finalOutputInt,(30+lengthInt + 27+lengthDouble+4), "The sum of all integers is %d; The sum of all doubles is %.2f",sumInt, sumDouble);
    char* finalOutput = (char*) malloc((30 + 27 + 1 + lengthInt + lengthDouble + 3) * sizeof(char));
    strcpy(finalOutput, finalOutputInt);
    strcat(finalOutput, finalOutputDouble);
    return finalOutputInt;
}

char* functionTwo( char* userInput) // function for question 2
{
    int inputLength = strlen(userInput);
    int counter = 0;
    char* this = (char*) malloc((inputLength+1) * sizeof(char));
    strcpy(this,userInput);
    while ( *userInput != '\0')
    {
        if ( isupper(*this) != 0)
        {
            *this = tolower(*this); //convert upper to lower
        }
        else if ( islower(*this) != 0)
        {
            *this = toupper(*this); //convert lower to upper
        }
        else
        {
            *this = *this;
        }

        this++;
        counter++;
        userInput++;
    }
    this = this - counter;
    userInput = userInput - counter;
    return this;
}

void functionOne()
{
    int* oneInt = (int*) malloc(1 * sizeof(int)); // 1a)
    free(oneInt);

    double* twoDouble = (double*) malloc( 2 * sizeof(double)); //1b)
    free(twoDouble);

    int* fiveInt = (int*) malloc ( 5 * sizeof(int)); //1c)
    printf("Question 1c: \n");
    for ( int i = 0; i < 5; i++)
    {
        *(fiveInt+i) = i;
        printf("%d ", *(fiveInt+i));
    }
    printf("\n");
    free(fiveInt);

    printf("Question 1d: \n");
    char* twentyChar = (char*) malloc (20 * sizeof (char)); // 1d)
    for (int i = 0; i < 20; i++)
    {
        *(twentyChar+i) = 65+i;
        printf("%c ", *(twentyChar + i));
    }
    printf("\n");
    free(twentyChar);

    printf("Question 1e: \n"); // 1e) 5 x 5 2D array, 5 rows, 5 cols
    char** twentyFiveChar = (char**) malloc( 5 * sizeof(char)); // row
    for ( int i = 0; i<5; i++)
    {
        *(twentyFiveChar+i) = (char*) malloc( 5 * sizeof(char));
    }

    for ( int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            *(*(twentyFiveChar + i) + j) = 'A' + i + j;
            printf("%c ", *(*(twentyFiveChar + i) + j));
        }
        printf("\n");
    }
    for ( int i = 0; i < 5; i++)
    {
        free(*(twentyFiveChar+i));
    }
    free(twentyFiveChar);
}

int main() {

    functionOne();
    printf("\n");
    printf("Question 1f: \n"); // 1f) 5 x 5 2D array, 5 rows, 5 cols
    char* one_f_new = (char*) malloc(5 * 5 * sizeof(char));
    int counter = 4;
    for ( int k = 0; k < 5 * 5; k++) {
        one_f_new[k] = 'A' + k;
        printf("%c ",  one_f_new[k]);
        if ( k == counter)
        {
            printf("\n");
            counter += 5;
        }
    }
    free(one_f_new);
    printf("\nQuestion 2:");
    char* word = "Hello! Welcome to C291-Spring-2021. Hope the classes have been going well!\n";
    printf("\n");
    char* testOne = functionTwo(word);
    printf("%s\n",testOne);
    free(testOne);

    /*char* string = "The of sum of all integers is;";
    char* string2 = " The sum of all doubles is ";
    printf("%d %d\n", strlen(string), strlen(string2)); */
    printf("\nQuestion 3:\n");
    char* String = "We have 5 cats, 123456.12312 dollars, 10.00 eggs and 555 loaves in my house!";
    char* stringOutput = functionThree(String);
    printf("%s", stringOutput);
    free(stringOutput);



    return 0;
}
