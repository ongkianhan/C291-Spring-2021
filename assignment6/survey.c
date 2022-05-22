/*
 * Assignment 6, C291-Spring-2021
 * Program to survey friends and family members about the 7 pressing global causes and their perceived importance.
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/12/2021
 *
 * causes
 * 1. FOOD SECURITY - food scarcity and famine
 * 2. MAJOR GLOBAL HEALTH ISSUES - malnutrition, COVID-19.
 * 3. GLOBAL CHILD HEALTH AND PRIMARY EDUCATION - children malnutrition, literacy and basic mathematics skills
 * 4. THE NEED FOR GENDER EQUALITY - women empowerment, sexual violence,
 * 5. EMPOWERMENT WORK IN AFRICA
 * 6. HABITAT AND BIODIVERSITY LOSS
 * 7. OCEAN CONSERVATION
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define ROW 7
#define COL 10


char *issues[7] = {"FOOD SECURITY", "MAJOR GLOBAL HEALTH ISSUES",
                   "GLOBAL CHILD HEALTH AND PRIMARY EDUCATION",
                   "GENDER EQUALITY", "EMPOWERMENT WORK IN AFRICA",
                    "HABITAT AND BIODIVERSITY LOSS", "OCEAN CONSERVATION"}; // 7 global issues as stated


int responses[7][10]; // row = issue, column = response
int statistics[7][10]; // same as responses, but for statistics
int points[7]; //points to take note of highest/lowest scores;
int highToLow[7]; //created to not destroy the order of points
char *highToLowIssues[7];

void initResponses(); // this initializes the responses randomly to save time. If you want to input your own values, please use take_Survey().
int update_response(int col);
void displayResponses();
void pointTotalCalculation();
void displayStatistics();
void printHTL();
void updateStatistics();
int take_Survey();

void initResponses()
{
    for ( int i = 0; i < 7; i++)
        for ( int j = 0; j < 10; j++)
        {
            *(*(responses+i)+j) = rand() % 10 + 1;   }
}

void displayResponses()
{
    printf("\n...Displaying responses...\n");
    for ( int k = 0; k < 10; k++)
    {
        if ( k == 0)
        {
            printf("%47d ", k+1);
        }
        else {
            printf("%3d ", k+1);
        }

    }
    printf("\n");
    for ( int i = 0; i < ROW; i++)
    {
        printf("%-42s: ", *(issues+i));
        for ( int j = 0; j < COL; j++)
        {
            printf("%3d ",*(*(responses+i) + j));
        }
        printf("\n");
    }
}

void displayStatistics()
{
    printf("\n------Displaying Statistics------\n");
    for ( int k = 0; k < 10; k++)
    {
        if ( k == 0)
        {
            printf("%47d ", k+1);
        }
        else {
            printf("%3d ", k+1);
        }
    }
    printf(" %s %7s %11s", "Average", "Total", "Responded");
    printf("\n");
    for ( int i = 0; i < ROW; i++)
    {
        int average = 0;
        int responded = 0;
        printf("%-42s: ", *(issues+i));
        for ( int j = 0; j < COL; j++)
        {
            printf("%3d ",*(*(statistics+i) + j));
            average += *(*(responses+i) + j);
            if ( *(*(responses+i) + j) > 0)
                responded++;
        }
        printf("%5d %9d %9d", average/10,average,responded);
        printf("\n");
    }
    pointTotalCalculation();

}


void printHTL() //print in descending order
{
    printf("\nPrinting the issues from highest to lowest points...\n");

    int *highToLowPtr = highToLow;
    int *startHTL = highToLow;
    for (int i = 0; i < 7; i++) {
        *(highToLowPtr + i) = *(points + i);
        *(highToLowIssues+i) = *(issues+i);
    }
    int *start = highToLow;
    int *pointsStart = points;

    // sort algorithm
    for (int i = 1 ; i <= 6; i++)
    {
        int j = i;
        while ( j > 0 && *(highToLowPtr+j-1) > *(highToLowPtr+j))
        {
            int temp = *(highToLowPtr+j);
            char* tempStr = *(highToLowIssues+j);
            *(highToLowPtr+j)   = *(highToLowPtr+j-1);
            *(highToLowIssues+j) = *(highToLowIssues+j-1);
            *(highToLowPtr+j-1) = temp;
            *(highToLowIssues+j-1) = tempStr;
            j--;
        }
    } // end sorting algorithm


    for (int k = 0; k < 7; k++)
    {
        printf("Issue %d: %s, %d\n", k + 1, *(highToLowIssues + k), *(start + k));
    }
}

void pointTotalCalculation() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            *(points + i) += *(*(responses + i) + j);
        }
    }
    int max = 0;
    int indexHigh = 0;
    int indexLow = 0;
    int low = *points;
    for (int i = 1; i < 8; i++) {
        if (*(points + i - 1) > max) {
            max = *(points + i - 1);
            indexHigh = i - 1;
        }
        if (*(points + i - 1) < low) {
            low = *(points + i - 1);
            indexLow = i - 1;
        }
    }
    printf("\nThe issue with the maximum points is: %s, %d\n", *(issues + indexHigh), *(points + indexHigh));
    printf("\nThe issue with the lowest points is: %s, %d\n", *(issues + indexLow), *(points + indexLow));

    printHTL();
}

void updateStatistics()
{

    for ( int i = 0; i < ROW; i++)
    {

        for ( int j = 0; j < COL; j++)
        {
            int count = 0;
            int index = j + 1;
            for ( int k = 0; k < 10; k++)
            {
                if ( *(*(responses+i) + k) == index)
                    count++;
            }
            *(*(statistics+i)+j) = count;
        }
    }
}

int update_response(int col)
{
    int counter = 0;
    int row = 0;
    while ( counter < 7)
    {
        printf("\nPlease rate the importance of this social issue - %s - 1 being least important, 10 being most important\n", *(issues+row));
        int thisResponse = 0;
        scanf(" %d", &thisResponse);
        if ( thisResponse > 10 || thisResponse < 0)
        {
            printf("\nPlease enter a number from 1 to 10!\n");
            continue;
        } // added this in to catch responses which are <0 and >10
        *(*(responses + row) + col) = thisResponse;
        row++;
        counter++;
    }
    if ( counter == 7 )
    {
        printf("\nThank you for your responses. We will move on to the next person.\n");
    }
    return 1;
}

int take_Survey()
{
    int count = 0;
    for ( int i = 0; i < 10; i++)
    {
        printf("\nHello friend or family member %c", 65+i);
        printf(",welcome to this survey.\n");
        count += update_response(i);
    }
    if ( count == 10)
    {
        printf("The survey is complete. Thank you all for your time!\n");
    }
    return 0;
}


int main() {
    srand(time(0));
    printf("\n------Welcome to this survey! Please indicate how you would rank the importance of each cause------\n");
    //take_Survey(); //If you want to input your own numbers, please uncomment this and comment initResponses()
    initResponses(); // For ease of execution, initResponses() is used here. Comment this out if you want to input your own numbers.
    displayResponses();
    updateStatistics();
    displayStatistics();
    return 0;
}
