//This program is supposed to scan 5 ints from the user
//Using those 5 ints, it should construct a linked list of 5 elements
//Then it prints the elements of the list using the PrintList function

#include <stdio.h>
#include <stdlib.h> // added this in for malloc

/*
 * Quiz9 file 2, C291-Spring-2021
 * Edited source code to implement linked list and traversal through the linked list.
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/21/2021
 *
 * Please read the comments for more details.
 */

struct Node{
    int data;
    struct Node* next;
};

void PrintList(struct Node* n);   //added declaration of function here

int main(void){
    struct Node *first,*second,*third,*fourth,*fifth;
    first = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node)); //changed realloc to malloc
    third = (struct Node*)malloc(sizeof(struct Node));  // changed calloc to malloc
    fourth = (struct Node*)malloc(sizeof(struct Node));
    fifth = (struct Node*)malloc(sizeof(struct Node));

    int i;
    printf("Please enter the integer value for your first node: \n");
    scanf(" %d", &i);   //changed to %d
    first -> data = i;  // changed . to ->

    printf("Please enter the integer value for your second node: \n");
    scanf(" %d", &i);   //changed to %d
    second -> data = i;    // changed . to ->
    first->next = second;

    printf("Please enter the integer value for your third node: \n");
    scanf(" %d", &i);    //changed to %d and &i
    third -> data = i;  // changed . to ->
    second->next = third;

    printf("Please enter the integer value for your fourth node: \n");
    scanf(" %d", &i);   //changed to &i
    fourth -> data = i;    // changed . to ->
    third->next = fourth;   //added ;

    printf("Please enter the integer value for your fifth node: \n");
    scanf(" %d", &i);   //changed to %d and &i
    fifth -> data = i;
    fourth->next = fifth;
    fifth->next = NULL;

    PrintList(first); // added ;
    free(first), free(second), free(third), free(fourth), free(fifth);
}

void PrintList(struct Node* n){     //definition of function
    while(n != NULL){       // changed to when != NULL
        printf(" %d", n->data); // changed %c to %d
        n = n->next;        // changed to n -> next to not traverse through 2 pointers at a time
    }

    printf("\n");
}