/* Instructions:
 *
 *
 1. Write a program to assign a grade to Student.
	Get the number of assignments from user.
  Get the students score out of how many points for each assignment.
	Calculate percentage and return the grade associated with a range of marks.
 2. The overall score range and the associated grades are as follows:
     a. [97-100] = A+
     b. [90-97] = A
     c. [80-90] = B
     d. [70-80] = C
     e. less than 70 is a failing grade and should be given an F
     e. greater than 100 or less than 0 is invalid and your code should print "Invalid"
 3. Use the skeleton code provided below to create a new function "printGrade" to assign a grade based on the score ranges.
 4. Use print statements in your function to display the grade. For example, if the input marks is 77, the output should read:
        "Your grade is : C"
 5. Please adhere to standard C syntax conventions and use comments to explain your code. Failure to do so will result in a penalty.
 *
 *
 * */

/*
 *  quiz3, grade range checker function.
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/



#include<stdio.h>


float printGrade(float average);        // create the function syntax and declare its structure
    //print the students grade based on their score in the class




int main(void){
    char ch = 'a';
    int score, maxScore;
    float totalScore = 0, totalMaxScore = 0;
    int assignments;                    // initialize all necessary variables, floats to display average accurately later on.
    //get the number of assignments from the student


    while(ch != 'n' || ch != 'N') {      // start while loop, check if user input ch is 'n' or 'N', which then terminates loop

        printf("How many assignments did you have? \n");
        scanf(" %d", &assignments);                              // asks user how many assignments they are going to input, and scan this number

        //get the student's score and the max score for each assignment
        printf("Enter your score(s) for all assignments \n");       // initialize for-loop based on how many assignments entered, to receive user input for
        for (int i = 0; i < assignments; i++) {                         // score for current test, and max score for current test
            printf("Please input your score, followed by max score (your score [space] max score): \nAssignment %d -\n",
                   i+1);
            scanf(" %d %d", &score, &maxScore);                         // scan and update the variables
            totalScore += score;                                        // totalScore and totalMaxScore will be used to calculate the average
            totalMaxScore += maxScore;
        }

        //calculate the student's percentage in the class using the information you've gathered.
        float percent;                                          // float percent created, since the grading scale is not restricted to integers only.
        percent = totalScore/totalMaxScore;                     // calculates percentage to see where the student falls in the grade range
        printf("Your totalScore / totalMaxScore is %d/%d = %f%%", (int) totalScore, (int) totalMaxScore, percent*100);
        printGrade(percent);                                        // prints the totalScore/totalMaxScore, which shows the percentage, and also returns the letter grade
        printf("\nDo you want to continue? (Y/N)\n");
        scanf(" %c", &ch);

        if ( ch == 'n' || ch == 'N')                    // if condition to check if user input == 'n' || 'N' to terminate the while loop
        {
            printf("\nYou have exited the program. Goodbye!");
            break;
        }

    }

    return 0;
    }


float printGrade(float score)                            // function prints the grade range according to the float input given, returns the corresponding grade ranges
{                                                                       // or returns an error message if the percentage is not within the upper and lower bounds.
    if ( score > 1 || score < 0)
        printf(" Your grade is invalid. Please try again.\n");

    else if ( score >= 0.97 && score <= 1){
        printf(" Your grade is : A+\n");
    }
    else if ( score >= 0.90 && score < 0.97){
        printf(" Your grade is : A\n");
    }
    else if ( score >= 0.80 && score < 0.90){
        printf(" Your grade is : B\n");
    }
    else if ( score >= 0.70 && score < 0.80){
        printf(" Your grade is : C\n");
    }
    else {
        printf(" Your grade is : F");
    }
    return 0;
}