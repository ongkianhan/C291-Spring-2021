/*
TODO:
Write a Program that does the following: Spam Checker
Research online some of the most common spam e-mail messages and words, and check your own
junk e-mail folder. Create a list of 30 words and phrases commonly found in spam messages. Write
a program in which the user enters an e-mail message. Read the message into a large character array
and ensure that the program does not attempt to insert characters past the end of the array. Then
scan the message for each of the 30 keywords or phrases. For each occurrence of one of these within
the message, add a point to the message’s “spam score.” Next, rate the likelihood that the message
is spam, based on the number of points it received. Print your results in a tabulator format showing
the words (highest likelihood first)
*/


/* spam words taken are from this url: https://www.autopilothq.com/blog/email-spam-trigger-words/ and from my junk email folder
 * 5 are chosen from each category of 6:
 * Manipulative words and phrases - 1. Act now 2. Action 3. Apply now 4. Apply online 5. Buy 6. Buy direct
 * Needy words and phrases - 38. Bonus 39. Email marketing 40. Free 41. For instant access 42. Free gift 43. Free trial
 * Sleazy words and phrases - 53. Click below 54. Deal 55. Direct email 56. Direct marketing 57. Do it today 58. Order now
 * Cheap words and phrases - 65. Avoid bankruptcy 66. Boss 67. Cancel 68. Card accepted 69. Certified 70. Cheap
 * Far-fetched words and phrases - 114. Billion dollars 115. Cash 116. Cash bonus 117. Consolidate debt and credit 118. Consolidate your debt 119. Double your income
 * Shady words and phrases - 159. Billing 160. Casino 161. Celebrity 162. Collect child support 163. Copy DVDs 164. Fast viagra delivery\
 */

#include <stdio.h>
#include <string.h>



int add_spam_score(char email[], char spam_word[], int index,int spam_word_count_bank[]);


/*int add_spam_score(char email[], char spam_word[], int index, int spam_word_count_bank[])
{
    int count = 0;
    const char *temp = email;
    const char *spam = spam_word;
    while ( (temp = strstr(temp, spam)))
    {
        count++;
        temp++;
    }
    spam_word_count_bank[index] = count;
    return 0;
} */

int main(void) {

    char spam_word_bank[36][100] = {"Act now", "Action","Apply now","Apply online", "Buy","Buy direct",               // Manipulative words and phrases
                                    "Bonus", "Email marketing", "Free", "For instant access",  "Free gift", "Free trial", // Needy words and phrases
                                    "Click below", "Deal", "Direct email",  "Direct marketing", "Do it today", "Order now", // Sleazy words and phrases
                                    "Avoid bankruptcy", "Boss", "Cancel" ,"Card accepted" ,"Certified", "Cheap", // Cheap words and phrases
                                    "Billion dollars" ,"Cash" , "Cash bonus" ,"Consolidate debt and credit" , "Consolidate your debt" , "Double your income", // Far-fetched words and phrases
                                    "Billing" ,"Casino" ,"Celebrity" , "Collect child support" ,"Copy DVDs" , "Fast viagra delivery"}; // Shady words and phrases

    int spam_word_bank_count[30];

    printf("Welcome to the Spam Checker. Please enter your entire email here: \n");
    char email[100000+1];           // create an array with maximum 100,000 input characters and 1 for the '\0' end character.
    fgets(email, 100000+1, stdin);
    char emailFinal [100000];

    size_t stringLengthEmail = strlen(email);
    strncpy(emailFinal, email, stringLengthEmail - 1) ;
    printf(" %s", emailFinal);
    int i = 0;
    int spam_score = 0;
    for ( i = 0; i < 36; i++)
    {
        int count = 0;
        const char *temp = emailFinal;

        char spam_word[100];
        strcpy(spam_word, spam_word_bank[i]);
        char (*p)[100] = &spam_word_bank[i];
        while ( (temp = strstr(temp, spam_word)) )
        {
            count++;
            temp++;
            spam_score++;
        }
        spam_word_bank_count[i] = count;

    }
    printf("\n");
    printf("==============Table of Spam Words================\n");

    for ( int j = 0; j < 36; j++)
    {
        char word[100];
        strcpy(word,spam_word_bank[j]);
        printf("For spam word %s", word);
        printf(" the count is: %d",spam_word_bank_count[j]);
        printf("\n");
    }

    printf("\nThe total spam word count is: %d\n", spam_score);
    if ( spam_score >= 30){
        printf("This is a spam email!\n");}
    else
    {
        printf("This is not a spam email!\n");
    }


    return 0;
}