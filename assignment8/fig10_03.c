// Fig. 10.3: fig10_03.c
// Card shuffling and dealing program using structures
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARDS 52
#define FACES 13

// card structure definition
struct card {
    const char *face; // define pointer face
    const char *suit; // define pointer suit
    size_t faceValue;
    size_t suitValue;
};

typedef struct card Card; // new type name for struct card

Card handOne[5], handTwo[5], bothHands[10];

// prototypes
void fillDeck(Card * const wDeck, const char * wFace[],
              const char * wSuit[]);
void shuffle(Card * const wDeck);
void deal(const Card * const wDeck);
int flush( Card array[], int start, int end);
int straight(Card array[], int start, int end);
int straightFlush( Card array[], int start, int end);
int largestCount( Card array[], int start, int end);
int fullHouseOrTriple( Card array[], int start, int end);
int singleOrDoublePair( Card array[], int start, int end);


int flush( Card array[], int start, int end) //if hand contains 4 other cards with same suit as first card, return 1 (flush). Else, return 0.
{
    int flushSuit = array[start].suitValue;
    int count = 0;
    for ( int i = start+1; i <= end; i++)
    {
        if ( flushSuit == array[i].suitValue)
        {
            count++;
        }
    }
    if ( count == 4)
        return 1;
    else
        return 0;
}

int straight(Card array[], int start, int end) // if hand royal straight, return 1. normal straight, return 2. Else, return 0.
{
    size_t count = 0;
    int straightType = 0; // if AKQJ10 royal straight, return 1. if normal straight, including A-2-3-4-5, return 2. else, return 0.
    if ( array[start].faceValue == 0 && array[start+1].faceValue == 9 && array[start+2].faceValue == 10 && array[start+3].faceValue == 11 && array[start+4].faceValue == 12) // edge case: royal straight
        return 1;
    else {
        for (int i = start+1; i <= end; i++) {
            if (array[i].faceValue - array[i - 1].faceValue == 1) {
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
int straightFlush( Card array[], int start, int end)
{
    // scenario 1. royal straight flush. return 2 ( royal straight == 1, flush ==  1)
    // scenario 2. normal straight flush. return 3 ( normal straight == 2, flush ==  1)
    // scenario 3. not straight flush. return 0

    if ( straight(array,start,end) == 0 || flush(array,start,end) == 0) //scenario 3
        return 0;
    else if ( straight(array,start,end) + straight(array,start,end) == 2 && straight(array,start,end) == 1) //scenario 1
    {
        printf("Your hand contains a royal flush!\n");
        return 2;
    }
    else{                                           //scenario 2
        printf("Your hand contains a straight flush!\n");
        return 3;
    }

}

int largestCount( Card array[], int start, int end) // checks the largest consecutive longest streak of card values.
{
    int max = 1;
    for ( int i = start; i < end + 1; i++)
    {
        int count = 1;
        for ( int j = i + 1; j < end + 1; j++)
        {
            if ( array[i].faceValue == array[j].faceValue)
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
        fullHouseOrTriple(array, start, end);
    }
    else if ( max == 2) // indicates you have at least a pair, but you might have 2 pairs
    {
        singleOrDoublePair(array, start, end);
    }
    else // you only have high cards, but it could be a straight/flush!
    {
        printf("Your hand contains High Card!\n");
    }
    return max;
}

int fullHouseOrTriple( Card array[], int start, int end) //checks if full house or triple. if full house, return 5. if triple, return 3.
{
    if ( ((array[start].faceValue == array[start+1].faceValue == array[start+2].faceValue)&& array[end-1].faceValue == array[end].faceValue) || ((array[start].faceValue == array[start+1].faceValue) && (array[end-2].faceValue == array[end-1].faceValue == array[end].faceValue)) )
    {
        printf("Your hand contains a full house!\n");
        return 5;

    }
    else {
        printf("Your hand contains a three of a kind!\n");
        return 3;
    }

}

int singleOrDoublePair( Card array[], int start, int end) // checks if there are 2 or only a single pair.
{
    int pair = 0, startLoop = start, endLoop = start + 1;
    while (startLoop != end)
    {
        if ( array[startLoop].faceValue == array[endLoop].faceValue)
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

void displayHand(const char *suit[], const char *faces[], Card array[], int start, int end) // sorts the hand via insertion sort, as well as displays the hand.
{
    int arraySize = end-start+1;
    Card arrayCopy[arraySize];
    for ( int i = 0; i < arraySize; i++)
    {
     arrayCopy[i].faceValue = array[i].faceValue;
        arrayCopy[i].suitValue = array[i].suitValue;
        arrayCopy[i].suit = array[i].suit;
        arrayCopy[i].face = array[i].face;
    }


    int i, keyFace, keySuit, j;
    // sorts first 5 cards - first hand
    for (i = 1; i < 5; i++) {
        arrayCopy[i].faceValue = array[i].faceValue;
        arrayCopy[i].suitValue = array[i].suitValue;
        char *suitCopy = arrayCopy[i].suit, *faceCopy = arrayCopy[i].face ;
        strcpy(suitCopy, array[i].suit);
        strcpy(faceCopy, array[i].face);
        j = i - 1;

        while (j >= 0 && arrayCopy[j].faceValue > keyFace) {
            arrayCopy[j+1].faceValue = array[j].faceValue;
            arrayCopy[j+1].suitValue = array[j].suitValue;
            strcpy(arrayCopy[j+1].suit , array[j].suit);
            strcpy(arrayCopy[j+1].face, array[j].face);
            j = j - 1;
        }

        arrayCopy[j+1].faceValue = array[j].faceValue;
        arrayCopy[j+1].suitValue = array[j].suitValue;
        strcpy(arrayCopy[j+1].suit ,array[j].suit);
        strcpy(arrayCopy[j+1].face, array[j].face);
    }


    //print first hand

    printf("\nYour first hand is: \n");
    for ( int k = 0; k < 5; k++)
    {
        printf("%s of %s\n",  arrayCopy[i].face,arrayCopy[i].suit);
    }
    printf("\n");
    largestCount(arrayCopy, 0 ,4);
    int checker = straightFlush(arrayCopy,0,4);
    if ( checker == 0)
    {
        if ( flush(arrayCopy,0,4) > 0)
            printf("Your first hand contains a flush!\n");
        else if ( straight(arrayCopy,0,4) > 0)
            printf("Your first hand contains a straight!\n");
    }

    //print second hand

    if ( arraySize == 10) {// sorts second 5 cards - second hand
        for (i = 6; i < 10; i++) {
            arrayCopy[i].faceValue = array[i].faceValue;
            arrayCopy[i].suitValue = array[i].suitValue;
            char *suitCopy = arrayCopy[i].suit, *faceCopy = arrayCopy[i].face ;
            strcpy(suitCopy, array[i].suit);
            strcpy(faceCopy, array[i].face);
            j = i - 1;

            while (j >= 5 && arrayCopy[j].faceValue > keyFace) {
                arrayCopy[j+1].faceValue = array[j].faceValue;
                arrayCopy[j+1].suitValue = array[j].suitValue;
                strcpy(arrayCopy[j+1].suit , array[j].suit);
                strcpy(arrayCopy[j+1].face, array[j].face);
                j = j - 1;
            }

            arrayCopy[j+1].faceValue = array[j].faceValue;
            arrayCopy[j+1].suitValue = array[j].suitValue;
            strcpy(arrayCopy[j+1].suit ,array[j].suit);
            strcpy(arrayCopy[j+1].face, array[j].face);
        }


        printf("\nYour second hand is: \n");
        for ( int k = 5; k < 10; k++)
        {
            printf("%s of %s\n",  arrayCopy[i].face,arrayCopy[i].suit);
        }
        printf("\n");
        largestCount(arrayCopy, 5 ,9);
        int checkerTwo = straightFlush(arrayCopy,0,4);
        if ( checkerTwo == 0)
        {
            if ( flush(arrayCopy,5,9) > 0)
                printf("Your first hand contains a flush!\n");
            else if ( straight(arrayCopy,5,9) > 0)
                printf("Your first hand contains a straight!\n");
        }
    }




}

int main(void)
{
    Card deck[CARDS]; // define array of Cards

    // initialize array of pointers
    const char *face[] = { "Ace", "Deuce", "Three", "Four", "Five",
                           "Six", "Seven", "Eight", "Nine", "Ten",
                           "Jack", "Queen", "King"};

    const int faceValue[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
    const int suitValue[] = { 0, 1, 2, 3};

    // initialize array of pointers
    const char *suit[] = { "Hearts", "Diamonds", "Clubs", "Spades"};

    srand(time(NULL)); // randomize

    fillDeck(deck, face, suit); // load the deck with Cards
    shuffle(deck); // put Cards in random order
    deal(deck); // deal all 52 Cards

    displayHand(suit,face,deck,0,4);
}

// place strings into Card structures
void fillDeck(Card * const wDeck, const char * wFace[],
              const char * wSuit[])
{
    // loop through wDeck
    for (size_t i = 0; i < CARDS; ++i) {
        wDeck[i].face = wFace[i % FACES];
        wDeck[i].suit = wSuit[i / FACES];
        wDeck[i].faceValue = i % FACES;
        wDeck[i].suitValue = i / FACES;

    }
}

// shuffle cards
void shuffle(Card * const wDeck)
{
    // loop through wDeck randomly swapping Cards
    for (size_t i = 0; i < CARDS; ++i) {
        size_t j = rand() % CARDS;
        Card temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

// deal cards
void deal(const Card * const wDeck)
{
    // loop through wDeck
    for (size_t i = 0; i < 10; ++i) {

        if ( i < 5)
        {
            if ( i == 0)
                printf("Hand One:\n");
            handOne[i].face = wDeck[i].face;
            handOne[i].suit = wDeck[i].suit;
            bothHands[i].face = wDeck[i].face;
            bothHands[i].suit = wDeck[i].suit;
            printf("%5s of %-8s%s", handOne[i].face, handOne[i].suit,
                   (i + 1) % 4 ? "  " : "\n");
            if ( i == 4)
                printf("\n");
        }
        else
        {
            if ( i == 5)
                printf("Hand Two:\n");
            handTwo[i].face = wDeck[i].face;
            handTwo[i].suit = wDeck[i].suit;
            bothHands[i].face = wDeck[i].face;
            bothHands[i].suit = wDeck[i].suit;
            printf("%5s of %-8s%s", handTwo[i].face, handTwo[i].suit,
                   (i + 1) % 4 ? "  " : "\n");
            if ( i == 9)
                printf("\n");
        }

    }
}



/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
