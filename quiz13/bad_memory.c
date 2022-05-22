#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void test1();
void test2();
void test3();
void test4();
char *getString( char* ptr );
//char *getString ();

char message[100] = "Hello World!";
char *message_ptr = message;

void test1()
{
    const int NUM_HEIGHTS = 3;
    int *heights = malloc(NUM_HEIGHTS * sizeof(int));     // note: first error here is the malloc size allocation is wrong
    for (int i = 0; i < NUM_HEIGHTS; i++)
    {
        heights[i] = i*i;
        printf("%d: %d\n", i , heights[i]);
    }
    free(heights);
    // also, remember to free your pointers!
}

void test2()
{
    const int NUM_WEIGHTS = 5;
    long long *weights = malloc(NUM_WEIGHTS * sizeof(weights));
    for (int i = 0; i < NUM_WEIGHTS; i++)
    {
        weights[i] = 100 + i;
        printf("%d: %lld\n", i , weights[i]);
    }
    // you don't know what the memory belongs to after you free it! Can't access the memory the same way
    // after you free a pointer, the information won't persist.
    weights[0] = 0;
    free(weights);
}

void test3() // run --leak-check=full
{
    const int NUM_HEIGHTS = 10;
    int *heights = malloc(NUM_HEIGHTS * sizeof(*heights));     // note: first error here is the malloc size allocation is wrong
    for (int i = 0; i < NUM_HEIGHTS; i++)
    {
        if( (heights = NULL)) // common bug! check = and ==
        {
            heights = malloc(NUM_HEIGHTS * sizeof(*heights));
        }

    }
    free(heights);
    // also, remember to free your pointers!
}


char* getString(char* ptr)   //bad memory
{
    // to fix this function, pass the pointer to the function!
    //char message[100] = "Hello World!";
    //char *ret = message;
    //return ret;
    return ptr;
    //return message;
}

/*char *getString()
{
    // to fix this function, pass the pointer to the function!
    char message[100] = "Hello World!";
    char *ret = message;
    return ret;
    //return message;
}
*/
void test4()
{
    //printf("\nString: %s\n", getString());
    printf("\nString: %s\n", getString(message_ptr));
}

int main() {

    //test1();
    //test2();
    //test3();
    test4();

    return 0;
}
