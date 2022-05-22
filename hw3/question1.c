/*
 *  Followed instructions for question 1 of assignment 3
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/


#include <stdio.h>

int main() {

    printf("%-*.*u\t1a)\n",12,6,1001);        //Print unsigned integer 1001 left justified in a 12-digit field with 6 digits.
    printf("0000%-*.*f\t1b)\n",8,3,7.350);  //Print 7.350 in a 8-digit field with preceding zeros.
    printf("%+d %d\t1c)\n",300,300);//Print 300 with and without a sign.
    printf("-%u\t\t1d)\n",300);//Print -300 as unsigned number.

    //Read a hexadecimal value into variable hex.
    unsigned int userHexa;
    printf("1e) Please input a hexadecimal value to be converted into a variable hexadecimal value.\n");
    scanf("%x",&userHexa);

    printf("The user entered: %X, in decimal is %d\n",userHexa,userHexa);

    //Read an octal value into variable octal.
    printf("1f) Please input an octal value to be converted into a variable octal value.\n");
    unsigned int userOct;
    scanf("%o",&userOct);

    printf("The user entered: %o, in decimal is %d\n",userOct,userOct);

    //Print 100 in hexadecimal form preceded by 0x.
    printf("1g) %#x\n",100);

    //Print 100 in octal form preceded by 0.
    printf("1h) %#o\n",100);

    //Read characters into array m until the letter z is encountered.
    char m[100];
    printf("%s","1i) The program will read characters into an array until letter z is encountered. Input: \n");
    scanf("%[^z]s",m);
    printf("The array contains %s\n",m);

    fflush(stdin);

    //Read a time of the form hh-mm-ss, storing the parts of the time in the integer variables hour, minute and
    // second. Skip the dash (-) in the input stream. Use the assignment suppression character.
    printf("\n1j) PLease input a time in the form of hh-mm-ss:\n");
    int hoursJ = 0, minutesJ = 0, secondsJ = 0;
    scanf(" %d%*c%d%*c%d",&hoursJ,&minutesJ,&secondsJ);
    int timeOne[3];
    timeOne[0] = hoursJ;
    timeOne[1] = minutesJ;
    timeOne[2] = secondsJ;
    printf("The time in hh:mm:ss is: ");
    for ( int i = 0; i < 3; i++) {
        if (timeOne[i] < 10) {
            if (i == 2) { printf("0%d", timeOne[i]); }
            else { printf("0%d:", timeOne[i]); }
        } else {
            if (i == 2) { printf("%d", timeOne[i]); }
            else { printf("%d:", timeOne[i]); }
        }
    }

    fflush(stdin);

    //Read a time of the form hh:mm:ss, storing the parts of the time in the integer variables
    // hour, minute and second. Skip the colons (:) in the input stream.
    // Do not use the assignment suppression character.
    printf("\n1k) PLease input a time in the form of hh:mm:ss :\n");
    int hoursK = 0, minutesK = 0, secondsK = 0;
    scanf("%d:%d:%d",&hoursK,&minutesK,&secondsK);
    int timeTwo[3];
    timeTwo[0] = hoursK;
    timeTwo[1] = minutesK;
    timeTwo[2] = secondsK;
    printf("The time in hh-mm-ss is: ");
    for ( int i = 0; i < 3; i++) {
        if (timeTwo[i] < 10) {
            if (i == 2) { printf("0%d", timeTwo[i]); }
            else { printf("0%d:", timeTwo[i]); }
        } else {
            if (i == 2) { printf("%d", timeTwo[i]); }
            else { printf("%d:", timeTwo[i]); }
        }
    }
    fflush(stdin);

    //Read a string of the form "characters" from the standard input.
    // Store the string in character array s. Eliminate the quotation marks from the input stream.
    char s[13];
    printf("%s","\n1l) Please type \"characters\"\nInput: ");
    scanf("%[^\n]s",s);
    for (int i = 0; i < 13; i++){
        if ( s[i] == 34)
        {
            s[i] = 32;
        }
    }
    printf("\n1l) The characters in array s are:%s", s);

    return 0;
}
