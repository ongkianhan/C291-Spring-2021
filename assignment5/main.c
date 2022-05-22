#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.c"


static int seat_assignment[7][20];     // A,B,D,E,F,H,I * 20 rows


void initializeArray(int array[][20]);

void initializeArray( int array[7][20]) // initialize all elements in the array to 0, apart from Row E. 2 indicates that it is blocked due to covid. 1 indicates it is taken by another passenger.
{
    memset(array, 0, sizeof(seat_assignment));
    for ( int i = 3; i < 4; i++)
    {
        for ( int j = 0; j < 20; j++)
        {
            array[i][j] = 2;
        }
    }
}

void display_seating_map(int array[7][20]);

void display_seating_map(int array[7][20])
{
    printf("1 represents the seat is taken. 2 represents the seat is blocked due to covid-protocols. 0 represents an empty seat.\n");
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

int choose_section();

int choose_section() // B = 66, E = 69, F = 70
{
    printf("Please choose your type of seat (F for first class, B for business class, E for economy. The default is economy: \n");
    char choice = 0;
    char choice2 = 0;

    scanf(" %c", &choice);
    if ( choice != 'F' && choice != 'B')
    {
        printf("You have been placed into the economy section by default. \n");
        choice = 'E';}
    if ( is_section_full('F') == 1)
    {
        printf("First class is full. Is it ok to be placed in Business class?\n");
        scanf(" %c", &choice2);
        if ( choice2 == 'Y' || choice2 == 'y')
        {
            choice = 66;
            return choice;
        }
        else
        {
            printf("You have not been assigned a seat. Returning to main menu...\n");
            return 100;
        }
    }
    else if (is_section_full('B') == 1 )
    {
        printf("Business class is full. Is it ok to be placed in Economy class?\n");
        scanf(" %c", &choice2);
        if ( choice2 == 'Y' || choice2 == 'y')
        {
            choice = 69;
            return choice;
        }
        else
        {
            printf("You have not been assigned a seat. Returning to main menu...\n");
            return 100;
        }
    }
    else
    {
        if (is_section_full('E') == 1)
        printf("Economy is full. Please take the next flight.\n");
        return 100;
    }
    return choice;
}


int upgrade_seat(char choice, char section);

int upgrade_seat(char choice, char section)
{
    int loop = 0;
    while ( loop != 1) {
        if (choice == 'Y' || choice == 'y') {
            if (section == 'B') {
                loop++;
                printf("You have been upgraded from Business Class to First class!\n");
                return 70;
            } else if (section == 'F') {
                printf("You are currently in the first class. You cannot upgrade!\n");
                return 0;
            } else {
                loop++;
                printf("You have been upgraded from Economy Class to Business Class!\n");
                return 66;
            }
        } else if (choice == 'n' || choice == 'N') {
            loop++;
            printf("No upgrades for customer.\n");
            return 0;
        } else {
            loop--;
            printf("You have selected an invalid option. Please type either Y or N");
        }
        loop++;
    }
}

int downgrade_seat(char choice, char section);

int downgrade_seat(char choice, char section) {
    int loop = 0;
    while (loop != 1) {
        if (choice == 'Y' || choice == 'y') {
            if (section == 'B') {
                printf("You have been downgraded from Business Class to Economy class!\n");
                loop++;
                return 69;
            } else if (section == 'E') {
                printf("You are currently in the economy class. You cannot downgrade!\n");
            } else {
                printf("You have been downgraded from First Class to Business Class!\n");
                loop++;
                return 66;
            }
        } else if (choice == 'n' || choice == 'N') {
            printf("No downgrades for customer.\n");
            loop++;
            return 0;
        } else {
            printf("You have selected an invalid option. Please type either Y or N");
            loop--;
        }
        loop++;
    }
    return 0;
}


void seat_random(char input);

/*void seat_random(char input)
{
    srand(time(0));
    int seat_row = 0, seat_row_upper = 0, seat_row_lower = 0;
    char seat_col = 0;
    int count = 0;
    char changeSeat = 0;
    while (( changeSeat == 'Y' || changeSeat == 'y') || count <= 4)
    {
        if ( count > 4)
        {
            printf("Since you cannot make up your mind, travel on the next flight! Quitting the program...\n");
            break;
        }

    seat_row_upper = 3;
    if ( input == 'F'){
        seat_row_lower = 1;}
    else if ( input == 'B') {
        seat_row_lower = 4;}
    else{
        seat_row_lower = 12;
        seat_row_upper = 8;}
    seat_row = rand() % (seat_row_upper+1-1) + seat_row_lower;
    seat_col = rand() % (8+1-1) + 65;
    while ( seat_col == 'E' || seat_col == 'C'|| seat_col == 0 ||  seat_col == 'G' || ) //I = 73,  A = 65
        {
            seat_row = rand() % (seat_row_upper+1-1) + seat_row_lower;
            seat_col = rand() % (8+1-1) + 65;
        }
    printf("Your initial seat assignment is: %c%d.\n",seat_col,seat_row);
    if( seat_col == 'A' || seat_col == 'I')
        printf("Your seat is a window seat. Do you want to change? Press Y to change and N to accept seat.\n");
    else
        printf("Your seat is an aisle seat. Do you want to change? Press Y to change and N to accept seat.\n");

    scanf(" %c", &changeSeat);
        if ( changeSeat == 'N' || changeSeat == 'n')
        {
            printf("Your seat assignment is %c%d. Thank you! Returning to menu...\n", seat_col, seat_row);
            return;
        }
    count++;
    }
    printf("Do you want to upgrade or downgrade? Type D to downgrade and U to upgrade, and N to keep your choice.\n");
    char up_or_downgrade = 0;
    scanf(" %c", &up_or_downgrade);
    if ( up_or_downgrade == 'N' || up_or_downgrade == 'n')
    {
        printf("Your seat assignment is %c%d. Thank you! Returning to menu...\n", seat_col, seat_row);
        return;
    }
    else if ( up_or_downgrade == 'u' || up_or_downgrade == 'U')
    {
        upgrade_seat(seat_col,)
    }
}*/

char return_plane_row(int i );
char return_plane_row(int i) // corresponds row Alphabet to array position
{
    if ( i == 0)
        return 'A';
    else if (i == 1)
        return 'B';
    else if (i == 2)
        return 'D';
    else if (i == 4)
        return 'B';
    else if ( i == 5)
        return 'H';
    else
        return 'I';
}

int choose_a_seat();

int choose_a_seat()
{
    int count = 0;
    char choice = 0;
    int finalRow = 0;
    int finalCol = 0;
    do {
        int row = 0, upper = 0, lower = 0, col = 0;
        int section = 0;
        section = choose_section();
        row = random_row();
        if ( section == 66) // Business
        {
            upper = 6;
            lower = 3;
        }
        else if ( section == 70) //First
        {
            upper = 2;
            lower = 0;
        }
        else // Economy
        {
            upper = 19;
            lower = 7;
        }
        col = random_col(upper,lower);
        while ( is_seat_taken(row,col) == 0) // 1 if taken, 0 if empty
        {
            assign_seat(row,col);
            printf("\nYour initial seat is %c%d.\n", return_plane_row(row),col+1);
            break;
        }
        count++;
        printf("Do you want to change seats? If yes, type Y. If not, type N. If you do not type Y/N, we will assign this seat to you.\n");
        scanf(" %c", &choice);
        if ( choice == 'n' || choice == 'N')
        {
            choice = 1;
            finalRow = row;
            finalCol = col;
            break; }
        else {
            choice = 0;
        }
        } while ( count <=4 && choice == 0);
    if ( count == 5)
    {
        printf("Since you cannot make up your mind, travel on the next flight!\n");
        return 0;
    }
    printf("\nYour initial seat is %c%d.\n", return_plane_row(finalRow),finalCol+1);
    return 0;
}

int updateTest (int input, int index);

/*int updateTest( int input, int index)
{
    test[index] += input;
}*/

int main() {
    srand(time(0));
    initializeArray(seat_assignment);
    display_seating_map(seat_assignment);
    choose_a_seat();
    /*for ( int i = 0; i < 5; i++)
    {
        updateTest( 5, i);
        printf("%d\n", test[i]);
        updateTest( 5, i);
        printf("%d\n", test[i]);
    }*/

    return 0;
}
