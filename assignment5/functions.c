//
// Created by user on 2/27/2021.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int seat_assignment[7][20];

int is_seat_unassigned(int row, int col);
int is_plane_row_full(int col);
int random_col(int upper, int lower); // col refers to 1-20
int random_row(); // row refers to A, B, D, E, F, H, I
int is_seat_taken(int row, int col);
int assign_seat(int row, int col);
int is_section_full(char section);

int is_seat_unassigned(int row, int col) //return 1 if full, return 0 if there is still space
{
    int seat = seat_assignment[row][col];
    if ( seat == 0)
        return 1;
    else
        return 0;
}

int is_plane_row_full(int col) //return 1 if full, return 0 if there is still space
{
    int full = 0;
    if ( seat_assignment[0][col] + seat_assignment[1][col] >= 1)
        full += 1;
    if ( seat_assignment[2][col]  == 1)
        full += 1;
    if (seat_assignment[4][col] == 1)
        full += 1;
    if (seat_assignment[6][col] +seat_assignment[5][col] >= 1)
        full += 1;
    if (full == 4)
        return 1;
    else
        return 0;
}

int random_col(int upper, int lower) // chooses from 1 - 20 randomly
{
    srand(time(0));
    return (rand() % (upper - lower) + lower);
}

int random_row() // chooses between A, B, D, F, H, I randomly. E is omitted
{
    srand(time(0));
    int output = 0;
    output = rand() % 7;
    while (output == 3)
    {
        output = rand() % 7;
    }
    return output;
}

int is_seat_taken(int row, int col) //return 1 if seat is taken, return 0 if seat is empty
{
    if (row == 0 || row == 5)
    {
        if (seat_assignment[row][col] + seat_assignment[row+1][col] >= 3)
            return 1;
        else
            return 0;
    }
    else if (row == 1 || row == 6)
    {
        if (seat_assignment[row-1][col] + seat_assignment[row-1][col] >= 3)
            return 1;
        else
            return 0;
    }
    else
    {
        if (seat_assignment[row][col] == 1 )
            return 1;
        else
            return 0;
    }
}

int assign_seat(int row, int col)
{
    if ( row == 0 || row == 5) {
        seat_assignment[row][col] = 1;
        seat_assignment[row+1][col] = 2;
    }
    else if (row == 1 || row == 6){
        seat_assignment[row-1][col] = 2;
        seat_assignment[row][col] = 1;
    }
    else{
        seat_assignment[row][col] = 1;
    }

    return 0;
}

int is_section_full(char section)   //return 1 if full, return 0 if there is still space
{
    int upperRange = 0, lowerRange = 0, sum = 0;
    if ( section == 'F')
    {
        upperRange = 2;
        lowerRange = 0;
    }
    else if ( section == 'B')
    {
        upperRange = 6;
        lowerRange = 3;
    }
    else
    {
        upperRange = 19;
        lowerRange = 7;
    }
    for ( int i = lowerRange; i < upperRange+1; i++)
    {
        sum += is_plane_row_full(i);
    }
    if ( sum == (upperRange - lowerRange))
    {
        return 1;
    }
    else
        return 0;
}