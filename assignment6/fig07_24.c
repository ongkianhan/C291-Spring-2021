// Fig. 7.24: fig07_24.c
// Card shuffling and dealing.

/*
 * Assignment 6, C291-Spring-2021
 * Program to shuffle deck and check the hand accordingly for combinations
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/12/2021
 *
 * Please read the comments for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

// prototypes

void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]); // dealing doesn't modify the arrays
void displayHand( const char *suit[], const char *faces[], const size_t arrayFace[5], const size_t arraySuits[5]);
int flush(const size_t arraySuit[5]);
int straight(const size_t arrayFace[5]);
int straightFlush( const size_t face[5], const size_t suit[5]);
int largestCount(const size_t face[5]);
int fullHouseOrTriple(const size_t face[5]);
int singleOrDoublePair(const size_t face[5]);

size_t handSuit[5];
size_t handFace[5];

int flush(const size_t array[5]) //if hand contains 4 other cards with same suit as first card, return 1 (flush). Else, return 0.
{
   int flushSuit = array[0];
   int count = 0;
   for ( int i = 1; i <5; i++)
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

int straight(const size_t arrayFace[5]) // if hand royal straight, return 1. normal straight, return 2. Else, return 0.
{
    size_t count = 0;
    int straightType = 0; // if AKQJ10 royal straight, return 1. if normal straight, including A-2-3-4-5, return 2. else, return 0.
    if ( arrayFace[0] == 0 && arrayFace[1] == 9 && arrayFace[2] == 10 && arrayFace[3] == 11 && arrayFace[4] == 12) // edge case: royal straight
        return 1;
    else {
        for (int i = 1; i < 5; i++) {
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
int straightFlush( const size_t face[5], const size_t suit[5])
{
    // scenario 1. royal straight flush. return 2 ( royal straight == 1, flush ==  1)
    // scenario 2. normal straight flush. return 3 ( normal straight == 2, flush ==  1)
    // scenario 3. not straight flush. return 0

    if ( straight(face) == 0 || flush(suit) == 0) //scenario 3
        return 0;
    else if ( straight(face) + straight(suit) == 2 && straight(face) == 1) //scenario 1
    {
        printf("Your hand contains a royal flush!\n");
        return 2;
    }
    else{                                           //scenario 2
        printf("Your hand contains a straight flush!\n");
        return 3;
    }

}

int largestCount(const size_t arrayFace[5]) // checks the largest consecutive longest streak of card values.
{
    int max = 1;
    for ( int i = 0; i < 5; i++)
    {
        int count = 1;
        for ( int j = i + 1; j < 5; j++)
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
        fullHouseOrTriple(arrayFace);
    }
    else if ( max == 2) // indicates you have at least a pair, but you might have 2 pairs
    {
        singleOrDoublePair(arrayFace);
    }
    else // you only have high cards, but it could be a straight/flush!
    {
        printf("Your hand contains High Card!\n");
    }
    return max;
}

int fullHouseOrTriple(const size_t arrayFace[5]) //checks if full house or triple. if full house, return 5. if triple, return 3.
{
    if ( ((arrayFace[0] == arrayFace[1] == arrayFace[2])&& arrayFace[3] == arrayFace[4]) || ((arrayFace[0] == arrayFace[1]) && (arrayFace[2] == arrayFace[3] == arrayFace[4])) )
    {
        printf("Your hand contains a full house!\n");
        return 5;

    }
    else {
        printf("Your hand contains a three of a kind!\n");
        return 3;
    }

}

int singleOrDoublePair( const size_t arrayFace[5]) // checks if there are 2 or only a single pair.
{
    int pair = 0, start = 0, end = start + 1;
    while (start != 4)
    {
        if ( arrayFace[start] == arrayFace[end])
        {
            pair++;
        }
        start++;
        end++;
    }

    if ( pair == 1)
        printf("Your hand contains a single pair!\n");
    else
        printf("Your hand contains two pairs!\n");

    return pair;
}

void displayHand(const char *suit[], const char *faces[], const size_t arrayFace[5], const size_t arraySuits[5]) // sorts the hand via insertion sort, as well as displays the hand.
{

    int i, keyFace, keySuit, j;
    for (i = 1; i < 5; i++) {
        keyFace = handFace[i];
        keySuit = handSuit[i];
        j = i - 1;

        while (j >= 0 && handFace[j] > keyFace) {
            handFace[j + 1] = handFace[j];
            handSuit[j+1] = handSuit[j];
            j = j - 1;
        }
        handFace[j + 1] = keyFace;
        handSuit[j+1] = keySuit;
    }

    printf("\nYour hand is: \n");
    for ( int k = 0; k < 5; k++)
    {
        printf("%s of %s\n",  faces[handFace[k]],suit[handSuit[k]]);
    }
    printf("\n");
    largestCount(arrayFace);
    int checker = straightFlush(arrayFace,arraySuits);
    if ( checker == 0)
    {
        if ( flush(arraySuits) > 0)
            printf("Your hand contains a flush!\n");
        else if ( straight(arrayFace) > 0)
            printf("Your hand contains a straight!\n");
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
void deal(unsigned int wDeck[][FACES], const char *wFace[],
   const char *wSuit[])
{
   // deal each of the cards
       for (size_t card = 1; card <= 5; ++card) {
           // loop through rows of wDeck
           for (size_t row = 0; row < SUITS; ++row) {
               // loop through columns of wDeck for current row
               for (size_t column = 0; column < FACES; ++column) {
                   // if slot contains current card, display card
                   if (wDeck[row][column] == card) {
                       printf("%5s of %-8s%c", wFace[column], wSuit[row], '\t');// 2-column format
                       handFace[card-1] = column;
                       handSuit[card-1] = row;
                   }
               }
           }

       }
}

