#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define override(a,b) a##b

int myFn(int a, int*b);

int myFn(int a, int *b) {
    a = *b + 1;
    return(a);
}

int main (){

    int *ptr;
    ptr = (int*) malloc(sizeof(int) * 10);


    int num1 = 5, num2 = 10;
    const int *cpci = &num1;
    cpci = &num2;
    printf("%d", *cpci);

    printf("\n");

    char myarray[] = "CSCI C291!";
    printf("%c\n", *(myarray+6));

    char* p = "HelloWorld!";
    p = p + 5;
    printf("%s\n",p);

    char name[20] = "helloClass";
    char *fullname = "helloClassof2021";
    printf("%d\n", strncmp(name,fullname,10));

    char message[] = "Today is Cold\n";
    int i = 0;
    char *pTr = message;

    while (*pTr++) i++;
    printf("%d\n", i);
    printf("%d\n", strlen(message));

    char *names2[] = {"Peyton", "Williams", "Manning"};
    printf("%c \n", *(*(names2+1)+2));

    char* names[] = {"A", "Very", "Weird", "Year"};
    char* pPtr = *names+2;
    printf("%c \n", *pPtr );


    int xyz=10;
    printf("%x\n", override(xy,z));

    struct Point {double x,y,z;} pt1={10,20,30}, *pt2=&pt1;

    printf("%f %f\n", pt1.x, pt2->x);


    struct Node {
        int value;
        struct Node *next;
    };

    struct Node n = {8, NULL};
    printf("%d\n", n.value);

    struct Politicians {
        int candidates[5];
        int*one;
    };


    int candidates[5]={56,65,11,22,44};
    struct Politicians elections2018, *ptr_e2018=NULL;
    for (int i = 0; i<5; i++)
        elections2018.candidates[i] = i+10;
    elections2018.one = candidates;
    ptr_e2018 = &elections2018;
    printf("%d ",elections2018.one[0]);
    printf("%d\n", *(ptr_e2018->one));



    int a=5,number=5;
    int *b = &number;
    a = myFn(a, b);
    printf("%d", a);

    return 0;

}



