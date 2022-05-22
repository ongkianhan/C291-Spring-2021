#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
 * Assignment 8 part 2, C291-Spring-2021
 * Answered questions accordingly and created functions
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/23/2021
 *
 * Please read the comments for more details.
 */

struct HealthProfile {

    char* firstName, *lastName, *gender; // char * for firstName, lastName and gender, which will be updated later
    int* height, *weight; // height in inches, weight in pounds
    struct dateOfBirth* DOB_ptr;
    struct familyHistory* FH_ptr;

} array[10], *ptr[10];

struct dateOfBirth
{
    int month,day,year;
};

struct familyHistory{
    bool bloodPressure,heartProblem,cancer;
};
struct dateOfBirth DOB_array[10] = {
        {3,14,1997},
        {6,15,1950},
        {9,15,2000},
        {1,20,1956},
        {4,1,1985},
        {5,16,1954},
        {7,24,1973},
        {7,28,2010},
        {12,9,1969},
        {11,5,1990}
};

struct familyHistory FH_array[10] = {
        {false, false, false},
        {true, true, true},
        {true, true, false},
        {true, false, false},
        {false, true, true},
        {false, true, false},
        {false, false, false},
        {true, false, true},
        {true, false, true},
        {true, false, true},
};

char *firstName[] = {"Kent", "James", "Jackson", "Brandon", "Jane", "Kira", "Adele", "Rose", "Bianca", "Riley"};
char* lastName[] = {"Ong", "Pollock", "Smith", "Woods", "Austen", "Light", "White", "Shields", "Rivers", "Lee"};
char* gender[] = {"male", "male", "male", "male", "female", "male", "female","female","female","female"};

int height[10] = {68, 60, 60, 54, 62, 70, 50, 55, 66, 52};
int weight[10]= {140, 160, 145, 180, 170, 190, 142, 185, 160, 165};

char sortedFirstName[10][20], sortedLastName; // according to BMI, highest - lowest
double sortedBMI[10];                           // according to BMI, highest - lowest
int multipleHealthIssue[10];              // indexes for patients with multiple health issues
int ageArray[10];                            //stores age of patients

struct HealthProfile initialize_indiv_health_profile();

struct HealthProfile initialize_indiv_health_profile()      // function to receive user input and create a structure of HealthProfile
{
    char firstName[20], lastName[20], gender[11], heartProblem[4], bloodPressure[4], cancer[4];
    int month, day, year, weight, height;
    printf("Please input your first name and last name:\n");
    scanf(" %s %s", firstName,lastName);
    printf("\nPlease input your gender(male, female or non-binary): \n");
    scanf(" %s", gender);
    printf("\nPlease enter your month, day and year for your date of birth: \n");
    scanf(" %d %d %d", &month, &day, &year);
    printf("\nPlease enter your height (in inches): \n");
    scanf(" %d", &height);
    printf("\nPlease enter your weight (in pounds): \n");
    scanf(" %d", &weight);
    printf("\nPlease indicate if any of your parents have had the following health issues: \n");
    printf("Heart Problem: Yes/No\n");
    scanf(" %s", heartProblem);
    printf("High Blood Pressure: Yes/No\n");
    scanf(" %s", bloodPressure);
    printf("Cancer: Yes/No\n");
    scanf(" %s", cancer);
    struct HealthProfile individual, *individual_ptr;
    individual_ptr = &individual;
    individual_ptr->firstName = firstName;
    individual_ptr->lastName = lastName;
    individual_ptr->gender = gender;
    individual_ptr->height = &height;
    individual_ptr->weight = &weight;
    individual_ptr->DOB_ptr->day = day;
    individual_ptr->DOB_ptr->month = month;
    individual_ptr->DOB_ptr->year = year;
    individual_ptr->FH_ptr->bloodPressure = (strcmp(bloodPressure,"Yes") == 0 ) ? true : false;
    individual_ptr->FH_ptr->heartProblem = (strcmp(heartProblem,"Yes") == 0 ) ? true : false;
    individual_ptr->FH_ptr->cancer = (strcmp(cancer,"Yes") == 0 ) ? true : false;


    printf("\n-------Here is your i------- \nFirst and Last name: %s %s\nGender: %s\nDate of birth: %d/%d/%d\nHeight(in): %d\nWeight(pounds): %d\n", firstName, lastName, gender, month,day,year,height,weight);
    printf("Family history:\nHigh Blood Pressure: %s\nHeart Problem: %s\nCancer: %s", individual_ptr->FH_ptr->bloodPressure == true ? "Yes" : "No", individual_ptr->FH_ptr->heartProblem == true ? "Yes" : "No",individual_ptr->FH_ptr->cancer == true ? "Yes" : "No");
    return individual;

}
void printPatientProfile( struct HealthProfile);

void printPatientProfile( struct HealthProfile profile)     // display information of a HealthProfile
{
    printf("\n-------Here is your i------- \nFirst and Last name: %s %s\nGender: %s\nDate of birth: %d/%d/%d\nHeight(in): %d\nWeight(lbs): %d\n", profile.firstName, profile.lastName, profile.gender, profile.DOB_ptr->month,profile.DOB_ptr->day,profile.DOB_ptr->year,*profile.height,*profile.weight);
    printf("Family history:\nHigh Blood Pressure: %s\nHeart Problem: %s\nCancer: %s", profile.FH_ptr->bloodPressure == true ? "Yes" : "No", profile.FH_ptr->heartProblem == true ? "Yes" : "No",profile.FH_ptr->cancer == true ? "Yes" : "No");
}

void bmiSorted( double bmiArray[], struct HealthProfile profileArray[]);

void bmiSorted( double bmiArray[], struct HealthProfile profileArray[])     // function to sort bmi in descending order and return ouput
{
    double bmiArrayCopy[10];
    char patientFirstNameCopy[10][20], patientLastNameCopy[10][20];
    char sortedFirstName[10][20], sortedLastName[10][20];
    int i, j;
    char* keyFirstName, *keyLastName;
    double keyBMI;
    //printf("BMI: \n");
    for ( i = 0; i < 10; i++)
    {
        bmiArrayCopy[i] = bmiArray[i];
        //printf(" %.2f", bmiArrayCopy[i]);
    }

    for ( i = 0; i < 10; i++)
    {
        strcpy(patientFirstNameCopy[i], profileArray[i].firstName);
        strcpy(patientLastNameCopy[i], profileArray[i].lastName);
        //printf(" %s %s\n", patientFirstNameCopy[i], patientLastNameCopy[i]);
    }

     for ( i = 0; i < 10; i++)
    {
        keyBMI = bmiArrayCopy[i];
        keyFirstName = patientFirstNameCopy[i];
        keyLastName = patientLastNameCopy[i];
        j = i - 1;

        while (j >= 0 && bmiArrayCopy[j] > keyBMI) {
            bmiArrayCopy[j + 1] = bmiArrayCopy[j];
            strcpy(sortedFirstName[j + 1],sortedFirstName[j]);
            strcpy(sortedLastName[j + 1 ], sortedLastName[j]);
            j = j - 1;
        }

        bmiArrayCopy[ j + 1 ] = keyBMI;
        strcpy(sortedFirstName[j+1], keyFirstName);
        strcpy(sortedLastName[j+1], keyLastName);

    }

    printf("\nSorted BMI list is (highest BMI to lowest BMI): \n");
     for ( i = 9; i >= 0; i--)
     {
         sortedBMI[i] = bmiArrayCopy[i];
         printf("Patient %d: %s %s %f\n", 10 - i, sortedFirstName[i], sortedLastName[i],bmiArrayCopy[i]);
     }

}

void updateMultipleHealthIssues( int array[], struct HealthProfile profileArray[]);

void updateMultipleHealthIssues (int inputArray[], struct HealthProfile profileArray[])  // function to check if patient has two or more of the three health issues
{
    for ( int i = 0; i< 10; i++)
    {
        int count = 0;
        if ( profileArray[i].FH_ptr->bloodPressure == true)
        {
            count++;
        }
        if ( profileArray[i].FH_ptr->cancer == true)
        {
            count++;
        }
        if ( profileArray[i].FH_ptr->heartProblem == true)
        {
            count++;
        }
        inputArray[i] = count;
    }
    printf("\nThe indexes of the patients who have more than 2 health issues are:");
    for ( int i = 0; i < 10; i++)
    {
        if ( inputArray[i] >= 2)
        {
            printf(" %d", i);
        }
    }
}

void updateAge(int array[], struct HealthProfile profileArray[]);

void updateAge(int inputArray[], struct HealthProfile profileArray[]) // simple function to udpdate the age of each patient
{
    int currentYear = 2021;
    for ( int i = 0; i < 10; i++)
    {
        int birthYear = profileArray[i].DOB_ptr->year;
        int age = currentYear - birthYear;
        inputArray[i] = age;
    }
}

void display_patientAge(int index, int arrayAge[]);

void display_patientAge(int index, int arrayAge[])      //simple function to display patientAge
{
    printf("Patient %s %s's age in years is %d\n", array[index].firstName, array[index].lastName, arrayAge[index]);
}

void patientStatistics(int ageAverage,int ageArrayInput[], double bmiArrayInput[], int healthIssueInput[]);

void patientStatistics(int ageAverage, int ageArrayInput[], double bmiArrayInput[], int healthIssueInput[]) // calculates and prints relevant information
{
    for ( int i =0; i < 10; i++)
    {
        if (( 30 <= bmiArrayInput[i] || bmiArrayInput[i] <= 18.5) && healthIssueInput[i] >= 2 && ageArrayInput[i] > ageAverage)
        {
            printf("\nPatient %d is at risk. His/her details are:\n", i);
            printf("Patient name: %s %s\n", array[i].firstName, array[i].lastName);
            printf("Age: %d\nBMI: %.2f\n", ageArrayInput[i], bmiArrayInput[i]);
            double maxHeartRate = 200 - ageArrayInput[i];
            printf("Maximum heart rate: %.2f\tTarget heart rate: %.2f - %.2f\n", maxHeartRate, maxHeartRate*0.55, maxHeartRate*0.75);
            printf("What is your normal heart rate? Please input an integer:\n");
            int heartRate = 0;
            scanf(" %d", &heartRate);
            if (( heartRate < maxHeartRate*0.55 || heartRate > maxHeartRate*0.75 ) && (array[i].FH_ptr->heartProblem == true || array[i].FH_ptr->bloodPressure == true))
            {
                printf("Your heart rate is outside the target heart rate, and you have a history of heart problem and/or blood pressure.\n");
                printf("You should visit your physician for a heart checkup.\n");
            }
            if( ( 30 <= bmiArrayInput[i] || bmiArrayInput[i] <= 18.5) && array[i].FH_ptr->cancer == true )
            {
                printf("\nYou are at risk of cancer, you should visit your oncologist for a cancer checkup.\n");
            }
        }

    }
}


int main()
{
    //initialize_indiv_health_profile(); please uncomment this to create your own profile
    printf("\n");

    // code below is used when instantiating the array of struct HealthProfile, and manipulated to have the correct output.

    for ( int i = 0; i < 10; i++)
    {
        array[i].firstName = firstName[i];
        array[i].lastName = lastName[i];
        array[i].gender = gender[i];
        array[i].height = &height[i];
        array[i].weight = &weight[i];
        array[i].DOB_ptr = &DOB_array[i];
        array[i].FH_ptr = &FH_array[i];
    } // initialize array
    double BMI[10], sortedBMI[10];
    for ( int i = 0; i < 10; i++)
    {
        BMI[i] = (*(array[i].weight)*703)/ (pow(*(array[i].height),2));
        sortedBMI[i] = BMI[i];
    }
    printf("\nBMI Values:\nUnderweight: less than %.2f\nNormal: between %.2f and %.2f\nOverweight: between %.2f and %.2f\nObese: %.2f or greater\n", 18.5, 18.5, 24.9,25.0,29.9,30.0);
    printf("\n");
    bmiSorted(BMI, array);


    updateMultipleHealthIssues(multipleHealthIssue,array);
    updateAge(ageArray, array);

    int sumOfAges = 0;
    for ( int i = 0; i < 10; i++)
    {
        sumOfAges+= ageArray[i];
    }
    int averageAge = sumOfAges/10;
    printf("\nThe average age is: %d\n", averageAge);

    patientStatistics(averageAge, ageArray, sortedBMI, multipleHealthIssue);
    printf("\n");
    display_patientAge(0,ageArray);

    return 0;
}