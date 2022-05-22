/*
 * Followed instructions for question 1 of assignment 4.
 * Created program to find the breakeven point of the Monte Carlo Simulation, and printed output accordingly.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numTrials = 10000;
int numPeople = 300;
int breakevenPointAverage = 0;
int breakevenCount = 0;
int breakeven = 0;
int breakevenPointRange[100];
int breakevenPointRangePointer = 0;


double run_simulation ( int userInput);

double run_simulation ( int input)
{
    int i = 0, j = 0, k = 0;
    double true_trials = 0;
    srand(time(0));
    for (i = 0; i < numTrials; i++)
    {
        int array[input];
        for (j = 0; j < input; j++)        //initialize array with values
        {
            int birthday = rand()%(365+1-1)+1;
            array[j] = birthday;
        }

        for (k = 0; k < input; k++)        // compare values in array
        {
            int nextNum = k + 1;
            if ( array[k] == array[nextNum])
            {
                true_trials++;
                break;
            }
        }
    }
    double probability = true_trials/10000;
    if( probability >= 0.5)
    {
        breakeven++;}
    if ( breakeven == 1)
    {
        printf(" %4d%30f%60s", input, probability,"<---- Breakeven Point\n");
        breakevenPointAverage += input;
        breakevenCount++;
        breakevenPointRange[breakevenPointRangePointer] = input;
        breakevenPointRangePointer++;
    }
    else
    {
        printf(" %4d%30f\n",input,probability);
    }

    return 0;
}


int main(void) {
    int start = 0;
    int i = 0, j = 0, k = 0;
    for (start = 1; start < 4; start++) {
        printf("=====================Test (%d)=========================\n", start);

        printf("\n%4s%50s\n", "(n)", "Computed Simulated Probability");
        printf("------------------------------------------------------\n");
        for (i = 2; i < numPeople + 1; i++) {
            run_simulation(i);}
        breakeven = 0;}

    int max = breakevenPointRange[0], min = breakevenPointRange[0];
    for (j = 1; j < 100; j++)
    {
        int temp = breakevenPointRange[j];
        if ( temp == 0)
            break;
        if ( temp > max)
            max = temp;
        if ( temp < min)
            min = temp;


    }
    printf("\nThe range of breakeven points is [%d,%d]", min,max);

    return 0;
}
