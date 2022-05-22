// Fig. 7.24: fig07_24.c
// Card shuffling and dealing.

/*
 * Assignment 8 q3, C291-Spring-2021
 * Program to shuffle deck and check the hand accordingly for combinations
 * Edited to shuffle deck and deal two hands, and check the hands accordingly
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/27/2021
 *
 * Please read the comments for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

// prototypes

//changed all functions from previous ones to intake new arrays which have a size of 10, which contains two hands.
// also included the start and end of each hand in the array of size 10. first hand: 0 - 4, second hand: 5 - 9.

void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]); // dealing doesn't modify the arrays
void displayHand( const char *suit[], const char *faces[], const size_t arrayFace[10], const size_t arraySuits[10]);
int flush(const size_t arraySuit[10], int start, int end);
int straight( const size_t arrayFace[10], int start, int end);
int straightFlush(  const size_t face[10], const size_t suit[10], int start, int end);
int largestCount( const size_t face[10], int start, int end);
int fullHouseOrTriple( const size_t face[10], int start, int end);
int singleOrDoublePair(const size_t face[10], int start, int end);

size_t handSuit[10];
size_t handFace[10];


int flush( const size_t array[10], int start, int end) //if hand contains 4 other cards with same suit as first card, return 1 (flush). Else, return 0.
{
    int flushSuit = array[start];
    int count = 0;
    for ( int i = start+1; i <= end; i++)
    {
        if ( flushSuit == array[i])
        {
            count++;
        }
    }
    if ( count == 4)
        return 1;
    else
        return 0;
}

int straight(const size_t arrayFace[10], int start, int end) // if hand royal straight, return 1. normal straight, return 2. Else, return 0.
{
    size_t count = 0;
    int straightType = 0; // if AKQJ10 royal straight, return 1. if normal straight, including A-2-3-4-5, return 2. else, return 0.
    if ( arrayFace[start] == 0 && arrayFace[start+1] == 9 && arrayFace[start+2] == 10 && arrayFace[start+3] == 11 && arrayFace[start+4] == 12) // edge case: royal straight
        return 1;
    else {
        for (int i = start+1; i <= end; i++) {
            if (arrayFace[i] - arrayFace[i - 1] == 1) {
                count++;
            } // if card[i] - card[i-1] = 1, this is a consecutive card. (array is already sorted)

        }
    }

    if ( count == 4 ) { // card[1] - card[0] = 1, card[2] - card[1] = 1, card[3] - card[2] = 1, card[4] - card[3] = 1. count = 4.
        return 2;
    }
    else
        return 0;
}
int straightFlush(  const size_t face[10],  const size_t suit[10], int start, int end)
{
    // scenario 1. royal straight flush. return 2 ( royal straight == 1, flush ==  1)
    // scenario 2. normal straight flush. return 3 ( normal straight == 2, flush ==  1)
    // scenario 3. not straight flush. return 0

    if ( straight(face,start,end) == 0 || flush(suit,start,end) == 0) //scenario 3
        return 0;
    else if ( straight(face,start,end) + straight(suit,start,end) == 2 && straight(face,start,end) == 1) //scenario 1
    {
        printf("Your hand contains a royal flush!\n");
        return 2;
    }
    else{                                           //scenario 2
        printf("Your hand contains a straight flush!\n");
        return 3;
    }

}

int largestCount( const size_t arrayFace[10], int start, int end) // checks the largest consecutive longest streak of card values.
{
    int max = 1;
    for ( int i = start; i < end + 1; i++)
    {
        int count = 1;
        for ( int j = i + 1; j < end + 1; j++)
        {
            if ( arrayFace[i] == arrayFace[j])
                count++;
        }
        if ( count > max)
            max = count;
    }
    if ( max > 4 || max < 1) // there is no way you can have a maximum streak of 5 or 0, that means your deck is rigged!
    {
        printf("The number of cards in your deck is incorrect. Please check your deck!\n");
        return 0;
    }
    else if ( max == 4) // if longest streak = 4, you definitely have a four of a kind.
        printf("Your hand contains a four of a kind!\n");
    else if ( max == 3) // indicates you have at least a triple, you might have a full house
    {
        fullHouseOrTriple(arrayFace, start, end);
    }
    else if ( max == 2) // indicates you have at least a pair, but you might have 2 pairs
    {
        singleOrDoublePair(arrayFace, start, end);
    }
    else // you only have high cards, but it could be a straight/flush!
    {
        printf("Your hand contains High Card!\n");
    }
    return max;
}

int fullHouseOrTriple( const size_t arrayFace[10], int start, int end) //checks if full house or triple. if full house, return 5. if triple, return 3.
{
    if ( ((arrayFace[start] == arrayFace[start+1] == arrayFace[start+2])&& arrayFace[end-1] == arrayFace[end]) || ((arrayFace[start] == arrayFace[start+1]) && (arrayFace[end-2] == arrayFace[end-1] == arrayFace[end])) )
    {
        printf("Your hand contains a full house!\n");
        return 5;

    }
    else {
        printf("Your hand contains a three of a kind!\n");
        return 3;
    }

}

int singleOrDoublePair( const size_t arrayFace[10], int start, int end) // checks if there are 2 or only a single pair.
{
    int pair = 0, startLoop = start, endLoop = start + 1;
    while (startLoop != end)
    {
        if ( arrayFace[startLoop] == arrayFace[endLoop])
        {
            pair++;
        }
        startLoop++;
        endLoop++;
    }

    if ( pair == 1)
        printf("Your hand contains a single pair!\n");

    if ( pair == 2)
        printf("Your hand contains two pairs!\n");

    return pair;
}

void displayHand(const char *suit[], const char *faces[], const size_t arrayFace[10], const size_t arraySuits[10]) // sorts the hand via insertion sort, as well as displays the hand.
{

    size_t firstHandFace[5], secondHandFace[5];
    size_t firstHandSuit[5], secondHandSuit[5];
    for ( int i = 0; i < 5; i++)    //copying to new arrays to ensure original array doesnt get affected.
    {
        firstHandFace[i] = handFace[i];
        secondHandFace[i] = handFace[i+5];
        firstHandSuit[i] = handSuit[i];
        secondHandSuit[i] = handSuit[i+5];
    }

    int i, keyFace, keySuit, j;
    // sorts first 5 cards - first hand
    for (i = 1; i < 5; i++) {
        keyFace = firstHandFace[i];
        keySuit = firstHandSuit[i];
        j = i - 1;

        while (j >= 0 && firstHandFace[j] > keyFace) {
            firstHandFace[j + 1] = firstHandFace[j];
            firstHandSuit[j+1] = firstHandSuit[j];
            j = j - 1;
        }
        firstHandFace[j + 1] = keyFace;
        firstHandSuit[j+1] = keySuit;
    }


    // sorts second 5 cards - second hand
    for (i = 1; i < 5; i++) {
        keyFace = secondHandFace[i];
        keySuit = secondHandSuit[i];
        j = i - 1;

        while (j >= 0 && secondHandFace[j] > keyFace) {
            secondHandFace[j + 1] = secondHandFace[j];
            secondHandSuit[j+1] = secondHandSuit[j];
            j = j - 1;
        }
        secondHandFace[j + 1] = keyFace;
        secondHandSuit[j+1] = keySuit;
    }

    size_t newSortedArrayFace[10], newSortedArraySuits[10]; // initialize and instantiate newly sorted faces and suits array of size 10
    for ( i = 0; i < 5; i++)
    {
        newSortedArrayFace[i] = firstHandFace[i];
        newSortedArrayFace[i+5] = secondHandFace[i];
        newSortedArraySuits[i] = firstHandSuit[i];
        newSortedArraySuits[i+5] = secondHandSuit[i];
    }

    //print first hand

    printf("\nYour first hand is: \n");
    for ( int k = 0; k < 5; k++)
    {
        printf("%s of %s\n",  faces[firstHandFace[k]],suit[firstHandSuit[k]]);
    }
    printf("\n");
    largestCount(newSortedArrayFace, 0 ,4);
    int checker = straightFlush(newSortedArrayFace,newSortedArraySuits,0,4);
    if ( checker == 0)
    {
        if ( flush(newSortedArraySuits,0,4) > 0)
            printf("Your first hand contains a flush!\n");
        else if ( straight(newSortedArrayFace,0,4) > 0)
            printf("Your first hand contains a straight!\n");
    }

    //print second hand

    printf("\nYour second hand is: \n");
    for ( int k = 0; k < 5; k++)
    {
        printf("%s of %s\n",  faces[secondHandFace[k]],suit[secondHandSuit[k]]);
    }
    printf("\n");

    largestCount(newSortedArrayFace, 5 ,9);
    int checkerTwo = straightFlush(newSortedArrayFace,newSortedArraySuits,5,9);
    if ( checkerTwo == 0)
    {
        if ( flush(newSortedArraySuits,5,9) > 0)
            printf("Your second hand contains a flush!\n");
        else if ( straight(newSortedArrayFace,5,9) > 0)
            printf("Your second hand contains a straight!\n");
    }


}

int main(void)
{
    // initialize deck array
    unsigned int deck[SUITS][FACES] = { 0 };

    size_t test_array_face[5] = {0,1,2,3,4}; //A 10 J Q K
    size_t test_array_suit[5] = {0,0,0,0,0}; // 0 = hearts, 1 = diamonds, 2 = clubs, 3 = spades
    srand(time(NULL)); // seed random-number generator

    shuffle(deck); // shuffle the deck

    // initialize suit array
    const char *suit[SUITS] =
            {"Hearts", "Diamonds", "Clubs", "Spades"};

    // initialize face array
    const char *face[FACES] =
            {"Ace", "Two", "Three", "Four",
             "Five", "Six", "Seven", "Eight",
             "Nine", "Ten", "Jack", "Queen", "King"};

    deal(deck, face, suit); // deal the deck
    displayHand(suit,face, handFace, handSuit); //shows you your hand. hand is sorted by insertion sort.


}

// shuffle cards in deck
void shuffle(unsigned int wDeck[][FACES])
{
    // for each of the cards, choose slot of deck randomly
    for (size_t card = 1; card <= CARDS; ++card) {
        size_t row; // row number
        size_t column; // column number

        // choose new random location until unoccupied slot found
        do {
            row = rand() % SUITS;
            column = rand() % FACES;
        } while(wDeck[row][column] != 0); // end do...while

        // place card number in chosen slot of deck
        wDeck[row][column] = card;
    }
}

// deal cards in deck
// edited this to deal 10 cards instead of 5
void deal(unsigned int wDeck[][FACES], const char *wFace[],
          const char *wSuit[])
{
    // deal each of the cards
    for (size_t card = 1; card <= 10; ++card) {
        // loop through rows of wDeck
        for (size_t row = 0; row < SUITS; ++row) {
            // loop through columns of wDeck for current row
            for (size_t column = 0; column < FACES; ++column) {
                // if slot contains current card, display card
                if (wDeck[row][column] == card) {
                    printf("%5s of %-8s%c", wFace[column], wSuit[row], '\t');// 2-column format
                    handFace[card - 1] = column;
                    handSuit[card - 1] = row;
                }
            }
        }

    }
}

