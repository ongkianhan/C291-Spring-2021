#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


int seat_assignment[7][20];      // A,B,D,E,F,H,I * 20 columns
int seat_assignment_sorted_by_manifest[7][20];
char seat_rows[] = {'A','B','D','E','F','H','I'};

char passenger_manifest_unsorted[140][30]; //name is restricted to 30 characters, can be changed later on.
char passenger_manifest_sorted[140][30]; // manifest in alphabetical order

// array is designed such that rows are designated by [A (window),B], [D,E,F] (middle section), [H,I (window)]
// A = 0, B = 1, D = 2, E = 3, F = 4, H = 5, I = 6; 7 rows

void print_passenger_manifest_bySeatAssignment(char passenger[140][30], int seat[7][20]);

void print_passenger_manifest_bySeatAssignment(char passenger[140][30], int seat[7][20])
{
    printf("\n...Printing passenger manifest...\n");
    printf("%s %50s\n", "Passenger Name", "Seat Number");
    for (int i = 0; i < 7; i++)
    {
        for ( int j = 0; j < 20; j++)
        {
            if ( seat[i][j] == 1)
            {
                printf("%s %50c%d\n", passenger[i*20+j], seat_rows[i], j+1);
            }
            else if (seat[i][j] == 0)
            {
                printf("%s %50c%d\n", "Unassigned", seat_rows[i], j+1);
            }
            else
            {
                printf("%s %39c%d\n", "Blocked due to covid.", seat_rows[i], j+1);
            }
        }
    }

}

void sort_passenger_manifest_alphabetically(char unsorted[140][30], int unsortedSeat[7][20]);

void sort_passenger_manifest_alphabetically(char unsorted[140][30], int unsortedSeat[7][20])
{
    char tempArray[30];
    char sorted[140][30];
    int sortedSeat[7][20];
    int temp;
    for ( int i = 0; i < 140; i++)
    {
        if (strcmp(unsorted[i], "Unassigned") != 0 && strcmp(unsorted[i], "Blocked due to covid.") != 0)
        strcpy(sorted[i], unsorted[i]);
    }

    for ( int i = 0; i < 7; i++)
    {
        for ( int j = 0; j < 20; j++)
        {
            sortedSeat[i][j] = unsortedSeat[i][j];
        }
    }

    for(int i = 0; i< 140; i++)
        for(int j = i + 1; j < 140;j++){
            if(strcmp(sorted[i], sorted[j])>0){
                strcpy(tempArray, sorted[i]);
                temp = sortedSeat[(i/20)][i%20];
                strcpy(sorted[i],sorted[j]);
                sortedSeat[(i/20)][i%20] = sortedSeat[(j/20)][j%20];
                strcpy(sorted[j],tempArray);
                sortedSeat[(j/20)][j%20] = temp;
            }
        }
}

void printBoardingPass(char seatRow, int col);

void printBoardingPass(char seatRow, int col)
{
    int seat_row_num,  seat_col;
    char section[3][15] = {"First-Class", "Business", "Economy"};
    seat_col = col;
    for ( int i = 0; i < 7; i++)
    {
        char compare = seat_rows[i];
        if ( seatRow == compare )
            seat_row_num = i;
    }
    int section_index;
    if ( seat_col <= 3)
        section_index  = 0;
    else if ( seat_col <= 7 && seat_col >= 4)
        section_index = 1;
    else
        section_index = 2;

    printf("\nYour boarding pass is as follows:\nPassenger Name: %s\tSeat: %c%d\tLevel: %s\n", passenger_manifest_unsorted[seat_row_num*20 +
            seat_col - 1], seatRow, seat_col, section[section_index]);

}

void initializeSeatArray(int array[][20]);

int is_section_full(int array[7][20], char section); // return 0 if empty seat is available, else return 1.

int is_section_full(int array[7][20], char section)
{
    int upper_col, lower_col;
    if ( section == 'F')
    {
        upper_col = 2;
        lower_col = 0;
    }

    if ( section == 'B')
    {
        upper_col = 6;
        lower_col = 3;
    }

    if ( section == 'E')
    {
        upper_col = 19;
        lower_col = 7;
    }
    bool empty_seat = false;

    for ( int i = 0; i < 7; i++)
    {
        for ( int j = lower_col; j <=upper_col; j++)
        {
            if (array[i][j] == 0)
            {
                empty_seat = true;
                return 0;
            }
        }
    }
    return 1;
}

void printSeatArray(int array[][20]);

void assignSeat(int array[][20], int col, int row, char seat_row[]);

void unassignSeat(int array[][20], int col, int row,char seat_row[]);

void blockSeat(int array[][20], int col, int row,char seat_row[]); // used for covid restrictions

void initial_seat_selection(int array[][20], char seat_row[], char name[]);

void upgrade_seat(int array[][20], char seat_row[], char option, int row, int col);

void downgrade_seat(int array[][20], char seat_row[], char option, int row, int col);


void initial_seat_selection(int array[][20], char seat_row[], char name[])
{
    srand(time(0));
    printf("\nPlease choose which section you want to be placed in! F for first-class, B for business class, E for economy. The default is economy"
           ".\n");
    char option;
    int col;
    scanf(" %c", &option);
    if ( is_section_full(array, option) == 1 && option == 'F' && is_section_full(array, 'B') == 1 && is_section_full(array, 'E') == 1)
    {
        printf("Sorry, but the entire flight is full. Please book the next flight. \n");
        return;
    }

    if(is_section_full(array, option) == 1 && option == 'F' && is_section_full(array, 'B') == 0 && is_section_full(array, 'E') == 0)
    {
        printf("The First-Class section is full. Is it ok to be shifted to Business Class? Enter Y (yes) or N (no). \n");
        scanf(" %c", &option);
        if ( option == 'Y')
            option = 'B';
        if ( option == 'N')
        {
            printf("The First-Class section is full. Is it ok to be shifted to Economy Class? Enter Y (yes) or N (no). \n");
            scanf(" %c", &option);
            if ( option == 'Y')
            {
                option = 'E';
            }
            else
            {
                printf("Since First-Class is full, and you do not want to be in Business Or Economy, please choose another flight. \n");
                return;
            }
        }
    }

    if(is_section_full(array, option) == 1 && option == 'F' && is_section_full(array, 'B') == 1 && is_section_full(array, 'E') == 0)
    {
        printf("The First-Class and Business section is full. Is it ok to be shifted to Economy Class? Enter Y (yes) or N (no). \n");
        scanf(" %c", &option);
        if ( option == 'Y')
            option = 'E';
        if ( option == 'N')
        {
                printf("Since First-Class and Business is full, and you do not want to be in Economy, please choose another flight. \n");
                return;
        }
    }

    int count = 0;
    char seat_option;
    while( count < 5)
    {
        if ( count == 4)
        {
            printf("We cannot repeat this seat selection process more than 3 times. Please choose the next flight.\n");
            break;
        }

        if ( option == 'F')
        {
            col = rand() % 2;

        }
        else if (option == 'B')
        {
            col = rand() % 3 + 3;
        }

        else
        {
            col = rand() % 12 + 7;
        }
        int row = rand() % 6;
        while (row == 3)
        {
            row = rand() % 6;
        }
        if ( seat_assignment[row][col] == 1)
        {
            continue;
        }
        printf("Your assigned seat is: %c%d\n", seat_rows[row],col + 1);
        printf("\nIf you are satisfied with your seat, please enter Y. Else, enter N to re-select a seat. \n");
        scanf(" %c", &seat_option);
        if ( seat_option == 'Y')
        {
            assignSeat(array, col, row, seat_row);
            strcpy(passenger_manifest_unsorted[row*20 + col], name);
            break;
        }

        else if ( seat_option == 'N')
        {
            count++;
        }

        else
        {
            printf("\nYou have entered an incorrect option. Please enter a valid option again.\n");
            continue;
        }

    }



}

void upgrade_seat(int array[][20], char seat_row[], char option, int row, int col)
{
    char upgradeOptions[][100] = { "From Economy (E) to either Business (B) or First-Class (F)", "From Business to First-Class (F)"};
    char upgrade[100];
    char upgrade_yes_or_no;
    char upgrade_to;
    int is_E_full, is_B_full, is_F_full;
    is_E_full = is_section_full(array,'E'), is_B_full = is_section_full(array, 'B'), is_F_full = is_section_full(array, 'F');
    if ( option == 'B')
    {
        strcpy(upgrade,upgradeOptions[1]);
    }
    if ( option == 'E')
    {
        strcpy(upgrade, upgradeOptions[0]);
    }
    printf("Do you want to upgrade your seat? You can only do this once. If yes, enter Y. If not, enter N.\n");
    scanf(" %c", &upgrade_yes_or_no);
    if ( upgrade_yes_or_no == 'Y' && option == 'E')
    {

        if ( is_F_full == 1 && is_B_full == 1)
        {
            printf("Sorry, we cannot upgrade you since there are no vacancies in both sections. \n");
            return;
        }
        else if (is_F_full == 1)
        {
            printf("Sorry, but the First-Class (%c) section is full. Do you mind changing to the Business (B) section?\n", 'F');
        }
        else
        {
            printf("Sorry, but the Business (%c) section is full. Do you mind changing to the First-Class (F) section?\n", 'B');
        }
        printf("Your upgrade choice(s): %s. Please type in the corresponding letter.\n", upgrade);
        scanf(" %c", &upgrade_to);
        printf("You have been successfully upgraded!. Your new seat is ");

    }
    else if ( upgrade_yes_or_no == 'Y' && option == 'B')
    {
        if ( is_F_full == 1 )
            printf("Sorry, but the First-Class (F) section is full. Upgrades are not available.\n");
    }
    else
    {
        printf("Your assigned seat is %c%d. Thank you!\n", seat_rows[row],col + 1);
    }
}

void downgrade_seat(int array[][20], char seat_row[], char option, int row, int col)
{
    char downgradeOptions[][100] = { "From First-Class (F) to either Business (B) or Economy (E).", "From Business (B) to Economy (E)."};
    char downgrade[100];
    char downgrade_yes_or_no;
    if ( option == 'B')
    {
        strcpy(downgrade,downgradeOptions[1]);
    }
    if ( option == 'F')
    {
        strcpy(downgrade,downgradeOptions[0]);
    }
    printf("Do you want to downgrade your seat? You can only do this once. If yes, enter Y. If not, enter N.\n");
    scanf(" %c", &downgrade_yes_or_no);
    if ( downgrade_yes_or_no == 'Y')
    {
        printf("Your downgrade choice: %s.\n", downgrade);
    }
    else
    {
        printf("Your assigned seat is %c%d. Thank you!\n", seat_rows[row],col + 1);
    }
}

void blockSeat(int array[][20], int col, int row,char seat_row[])
{

    printf("The seat %c%d is blocked. \n", seat_row[row], col + 1);
        array[row][col] = 2;
}

void assignSeat(int array[][20], int col, int row, char seat_row[])
{
    if ( array[row][col] == 0)
    {
        printf("Your assigned seat is %c%d. It is a %s seat.\n", seat_row[row], col + 1, row == 0 || row == 6 ? "Window" : "Aisle");
        array[row][col] = 1;

        if( row == 0 || row == 5)
        {
            array[row+1][col] = 2;
        }

        if( row == 1 || row == 6)
        {
            array[row-1][col] = 2;
        }
    }

}

void unassignSeat(int array[][20], int col, int row,char seat_row[])
{
    printf("The seat %c%d is unassigned. \n", seat_row[row], col + 1);
    array[row][col] = 0;
}

void printSeatArray(int array[][20])
{
    printf("Printing current seating map....\n");
    printf("\n1 represents the seat is taken. 2 represents the seat is blocked due to covid-protocols. 0 represents an empty seat.\n\n");
    printf("   ");
    for ( int k = 1; k < 21; k++)
    {
        if( k >= 10)
        {
            printf("%3d", k);
        }
        else {
            printf("%2d ", k);}
    }
    printf("\n");
    char col = 'A';
    for ( int i = 0, j = 0; i < 7; i++)
    {

        if( col == 'C' || col == 'G')
        {
            col = col + 1;
            printf("\n");
        }
        printf("%c  ", col );
        col++;
        for ( j = 0; j < 20; j++)
        {
            printf("%2d ", seat_assignment[i][j]);
        }
        printf("\n");
    }
}

void initializeSeatArray(int array[][20])
{
    for ( int i = 0; i < 7; i++)    //block row E. 0 = empty, 1 = taken, 2 = blocked due to covid
    {
        int value = 0;
        for (int j =0; j < 20; j++)
        {
            if ( i == 3)
            {
                value = 2;
            }
            array[i][j] = value;
        }
    }
}


int main() {
    srand(time(0));
    initializeSeatArray(seat_assignment);
    printSeatArray(seat_assignment);
    initial_seat_selection(seat_assignment,seat_rows, "Kent Ong");
    initial_seat_selection(seat_assignment,seat_rows, "Brayden Lamar");
    printSeatArray(seat_assignment);
    print_passenger_manifest_bySeatAssignment(passenger_manifest_unsorted, seat_assignment);
    printBoardingPass('F',1);
    printBoardingPass('F',2);
    printBoardingPass('A',1);
    printBoardingPass('A',2);
    printBoardingPass('B',1);
    printBoardingPass('B',2);
    printBoardingPass('D',1);
    printBoardingPass('D',2);
    printBoardingPass('H',1);
    printBoardingPass('H',2);
    /*char input ='A';

    do {
        switch (input) {

            case '1':

                break;

        }


    } while */

    /*for ( int i = 0; i < 5; i++)
    {
        updateTest( 5, i);
        printf("%d\n", test[i]);
        updateTest( 5, i);
        printf("%d\n", test[i]);
    }*/

    return 0;
}
