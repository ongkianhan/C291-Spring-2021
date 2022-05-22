#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Assignment 8 part 1, C291-Spring-2021
 * Answered questions accordingly and created functions
 * Author: Kent Ong
 * Bloomington, IN
 * Last edited:  Spring 2021, 03/23/2021
 *
 * Please read the comments for more details.
 */

struct patientinformation {
    char patient_name[20];
    char* abbreviated_name;
    unsigned int age;
    struct {
        char phone_number[11];
        char address[60];
        char city[20];
        char state[3];
        int zipCode;
    } physical_address;
    bool istested;
    struct {
        char* test_date;
        bool istested_positive;
    } covid_results ;
} healthRecord, *healthRecord_ptr;



int main() {
    healthRecord_ptr = &healthRecord;
    //Question 1a
    strcpy(healthRecord.patient_name, "Kent Ong");
    printf("Question 1a) %s\n",healthRecord.patient_name);
    //Question 1b
    printf("\nQuestion 1b) %s\n",healthRecord_ptr->patient_name);
    //Question 1c
    healthRecord.abbreviated_name = "KO";
    printf("\nQuestion 1c) %s\n",healthRecord.abbreviated_name);
    //Question 1d
    printf("\nQuestion 1d) %s\n",healthRecord_ptr -> abbreviated_name);
    //Question 1e
    char test_abbreviated_name[4] = "KO*"; // changed KO to KO* to indicate its pointing to something new
    healthRecord.abbreviated_name = test_abbreviated_name;
    printf("\nQuestion 1e) %s\n",healthRecord_ptr -> abbreviated_name);
    //Question 1f
    healthRecord.physical_address.zipCode = 47403;
    printf("\nQuestion 1f) %d\n",healthRecord.physical_address.zipCode);
    //Question 1g
    printf("\nQuestion 1g) %d\n",healthRecord_ptr->physical_address.zipCode);
    //Question 1h
    printf("\nQuestion 1h) %s\n",healthRecord.istested ? "positive" : "negative"); // changed 0 and 1 to negative and positive respectively
    //Question 1i
    printf("\nQuestion 1i) %s\n",healthRecord.covid_results.istested_positive ? "Yes (Positive)" : "No (Negative)"); // changed 0 and 1 to No and Yes respectively
    //Question 1j
    healthRecord.covid_results.test_date = "03/15/2021";
    printf("\nQuestion 1j) %s\n",healthRecord_ptr->covid_results.test_date);
    //Question 1k
    struct patientinformation testArray[3];
    printf("\nQuestion 1k) \n");
    for (int i = 0; i < 3; i++)
    {
        testArray[i].physical_address.zipCode = 47410 + i;
        printf("Record testArray[%d]: %d\n", i+1, testArray[i].physical_address.zipCode);
    }
    printf("4th record which was previously initialized: %d\n", healthRecord.physical_address.zipCode);
    printf("5th record (ptr) which was previously initialized: %d\n", healthRecord_ptr->physical_address.zipCode);
    //Question 1l
    printf("\nQuestion 1l) \n");
    struct patientinformation* testArray_ptr = (struct patientinformation *) &testArray;
    for (int i = 0; i < 3; i++)
    {
        (testArray_ptr+i) ->covid_results.istested_positive = true;
        printf("Record testArray[%d]: %s\n", i+1, (testArray_ptr+i) -> covid_results.istested_positive ? "Yes. Positive" : "No. Negative"); // changed 0 and 1 to No and Yes respectively
    }
    healthRecord.covid_results.istested_positive = true;
    printf("4th record which was previously initialized: %s\n", healthRecord.covid_results.istested_positive ? "Yes. Positive" : "No. Negative"); // changed 0 and 1 to No and Yes respectively
    printf("5th record (ptr) which was previously initialized: %s\n", healthRecord_ptr->covid_results.istested_positive ? "Yes. Positive" : "No. Negative"); // changed 0 and 1 to No and Yes respectively
    return 0;
}
