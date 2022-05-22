/*
Given program provides the users with options to input information about students. Once the user has input the information, the user can choose one of the following:
1. Determine and print the highest marks achieved by any student
2. Determine and print the name of student with median of marks among all the students
3. Print the names of the students that scored less than 50 marks
Fix the code so that the program works as expected. The code has around 8 errors that you would need to fix.
There are no intended errors in any of the print or the main function
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


struct Student
{
    char *firstName;
    char *lastName;
    int rollNumber;
    float marks;
};

struct Node
{
    struct Student *student;
    struct Node *next;
};

struct Node* createNode();
struct Student* createStudent(char *firstName, char *lastName, int rollNumber, float marks);
void addStudent(struct Node *head);
void printStudent(struct Student *student);
void printStudents(struct Node *head);
float getHighestMarks(struct Node *head);
struct Student *getStudentWithMedianMarks(struct Node *head);



// allocates memory for a new node in a linked list and returns a pointer
struct Node* createNode()      // 2) removed * to create a struct Node function
{
    struct Node *current = (struct Node*)malloc(sizeof(struct Node));
    return current;
}


// allocates memory for a new student and returns a pointer
struct Student* createStudent(char *firstName, char *lastName, int rollNumber, float marks)
{
    struct Student *student = (struct Student*)malloc(sizeof(struct Student));  // 3) changed type cast of malloc to struct Student*
    // 4) changed all of the . to ->, since we are using the student pointer
    strcpy(student -> firstName, firstName);
    strcpy(student -> lastName, lastName);
    student -> rollNumber = rollNumber;
    student -> marks = marks;
    return student;
}

void addStudent(struct Node *head)
{
    char firstName[20];
    char lastName[20];
    int rollNumber;
    float marks;

    printf("Enter first name and last name of student:\n");
    scanf(" %s %s", firstName, lastName);

    printf("Enter roll number of the student:\n");
    scanf(" %d", &rollNumber);

    printf("Enter marks obtained by the student:\n");
    scanf(" %f", &marks);

    struct Node *temp = head;

    // for the first node, head, student is not initialized so we check if it is the first node by checking if student not init
    // since head is already initialized in the main, we dont want to reinit it here
    if (temp->student != NULL)
    {
        // traverse to the end of the linked list
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp = createNode();
    }
    temp->student = createStudent(firstName, lastName, rollNumber, marks);
}


// prints the student referenced by the pointer to the student passed as argument
void printStudent(struct Student *student)
{
    if (student == NULL)
    {
        return;
    }
    printf("\nRoll No: %d\nName: %s %s\nMarks: %.2f\n", student->rollNumber, student->firstName, student->lastName, student->marks);
}

// prints all the students
void printStudents(struct Node *head)
{
    if (head == NULL || head->student == NULL)
    {
        printf("\nNo Students Entered Yet\n");
        return;
    }

    printf("\nPrinting Names of All Students\n");
    struct Node *temp = head;
    while (temp -> student != NULL)
    {
        printStudent(temp->student);
        temp = temp->next;
    }
    printf("\n\n");
}

float getHighestMarks(struct Node *head)        // changed return type to float
{

    if (head == NULL || head->student == NULL)
    {
        printf("\nNo Students Entered Yet\n");
        return 0;
    }

    float max = 0;
    while (head != NULL)
    {
        if (head->student->marks > max) //changed all references for pointers from . to ->
        {
            max = head->student->marks; //changed all references for pointers from . to ->
        }
        head = head->next;  // changed this to ->
    }
    return max;
}

struct Student *getStudentWithMedianMarks(struct Node *head)
{

    if (head == NULL || head->student == NULL)
    {
        printf("\nNo Students Entered Yet\n");
        return NULL;
    }

    int totalNumberOfStudents = 0;

    struct Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
        totalNumberOfStudents++;
    }

    int medianPosition = totalNumberOfStudents/2;       // median position should be total/2
    int currentPosition = 1;
    temp = head;
    while (temp != NULL)
    {
        if (currentPosition == medianPosition)
        {
            return temp -> student;                     // changed to temp -> student
        }
        currentPosition++;
        temp = temp->next;
    }
    printf("\n\n");
}

void getStudentsWithLessThanFifty(struct Node *head)
{
    if (head == NULL || head->student == NULL)      // changed head = NULL to head == NULL
    {
        printf("\nNo Students Entered Yet\n");
        return;
    }

    struct Node* temp = head;           // changed to Struct Node*
    while (temp != NULL)
    {
        if (temp->student->marks < 50)
        {
            printStudent(temp->student);
        }
        temp = temp->next;
    }
    printf("\n\n");
}

int main()
{

    int option = 5;
    struct Node *head = createNode();
    float highestMarks = 0;         // changed to float
    struct Student *medianStudent = NULL;
    do
    {
        printf("Please choose an option\n1. Add a student\n2. Print highest marks by student\n3. Print name of student with median marks\n4. Print names of students that scored less than 50\n5. Print All\n6. Exit\n");
        scanf(" %d", &option);

        switch (option)
        {
            case 1:
                addStudent(head);
                break;
            case 2:
                highestMarks = getHighestMarks(head);
                printf("\n\nHighest Marks Among All Students is %f\n\n", highestMarks);     //changed to %f
                break;

            case 3:
                medianStudent = getStudentWithMedianMarks(head);
                printf("\n\nStudent with Median Marks is\n");
                printStudent(medianStudent);

                break;

            case 4:
                getStudentsWithLessThanFifty(head);

                break;

            case 5:
                printStudents(head);
                break;

            default:
                printf("\n\nGoodbye\n\n");
                exit(0);
                break;
        }
    } while (true);

    return -1;
}