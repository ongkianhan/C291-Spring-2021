#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <io.h>
#include <string.h>


struct patient {
    char lastName[15];
    char firstName[15];
    char gender;
    struct covidData *covidInfo;
};

struct covidData {
    bool isCovidPositive;
    struct Date *testDate;
};

struct Date
{
    int month;
    int day;
    int year;
};


void initializePatientArray( struct patient array[30]);


void initializePatientArray(struct patient array[30])
{
    struct patient *ptr = malloc((sizeof(struct patient)  + sizeof(struct Date) + sizeof(struct covidData))* 30);
    for ( int i = 0; i < 30; i++)
    {
        (ptr + i)->covidInfo = malloc(sizeof(struct covidData));
        (ptr + i) -> covidInfo -> testDate = malloc(sizeof(struct Date));
        strcpy((ptr+i) ->lastName,"unassigned");
        strcpy( array[i].lastName, (ptr+i) ->lastName);
        strcpy((ptr+i) ->firstName, "");
        strcpy( array[i].firstName, (ptr+i) ->firstName);
        (ptr + i)->gender = 'M';
        array[i].gender = (ptr + i)->gender;
        (ptr+i) -> covidInfo ->isCovidPositive = 0;
        (ptr+i) -> covidInfo ->testDate->month = 1;
        (ptr+i) -> covidInfo ->testDate->day = 1;
        (ptr+i) -> covidInfo ->testDate->year = 2021;
        printf("Patient %d: %s %s %c %d %d-%d-%d\n", i+1, (ptr +i) ->lastName, (ptr +i) ->firstName, (ptr +i) ->gender, ((ptr+i) -> covidInfo
        ->isCovidPositive == 0) ? 0 : 1, (ptr+i) -> covidInfo ->testDate->month,(ptr+i) -> covidInfo ->testDate->day, (ptr+i) -> covidInfo
        ->testDate->year);
    }
    free(ptr);
    /*for ( int i = 0; i < 30; i++) {
        printf("Patient %d: %s %s %c %d %d-%d-%d\n", i+1, patientArray[i].lastName, patientArray[i].firstName, patientArray[i].gender, patientArray[i]
                       .covidInfo->isCovidPositive,
               patientArray[i].covidInfo->testDate->month,
               patientArray[i].covidInfo->testDate->day,patientArray[i].covidInfo->testDate->year); } */
}

void copyOddLines( FILE *writingFile, FILE *readingFile);

void copyOddLines( FILE *writingFile, FILE *readingFile)
{
    fseek(writingFile,0,0);
    fseek(readingFile,0,0);
    int removeFile = remove("name_age_data.txt");
    if( removeFile == 0)
    {
        printf("File successfully removed");
    }

    size_t line_size = 0;
    int line_count = 0;
    size_t line_buffer_size = 0;
    char *line;
    line = malloc(sizeof(char) * 200);
    while (getline(&line,&line_buffer_size, readingFile) != -1 && line_count <= 30)
    {
        if (line_count == 0)
        {
            fprintf(writingFile, "%s", line);
        }
        else if ( line_count % 2 == 1)
        {
            fprintf(writingFile, "%s", line);
        }
        else
        {
            fprintf(writingFile, "%d\t%17s\t%17s\t%2s\t%5d\t%12s\n", line_count, "unassigned", "", "", 0, "1-1-2021");
        }
        line_count++;
    }
    free(line);

}


int main() {
    FILE *writingFile, *readingFile;
    readingFile = fopen("patient_information.txt","r");
    writingFile = fopen("name_age_data.txt", "w");
    fprintf(writingFile,"Patient #\tLast Name\tFirst Name\tGender\tisCovidPositive\tTest Date\n");
    for ( int i = 0; i < 30; i++)
    {
        fprintf(writingFile, "%d\t%17s\t%17s\t%2s\t%5d\t%12s\n", i+1, "unassigned", "", "", 0, "1-1-2021");
    }
    rewind(writingFile);

    struct patient patientArray[30], *ptr;
    ptr = patientArray;
    initializePatientArray(patientArray);
    //printf("%s %s %c %d %d %d %d", patientArray[0].lastName, patientArray[0].firstName, patientArray[0].gender,ptr ->covidInfo->isCovidPositive,1,1,0);
    // patientArray[0]
    //    .covidInfo->testDate->month,
    //           patientArray[0].covidInfo->testDate->day, patientArray[0].covidInfo->testDate->year, ((patientArray[0].covidInfo->isCovidPositive
    //                                                                                                 == false) ? 0 : 1)

    copyOddLines(writingFile,readingFile);
    fclose(writingFile);
    fclose(readingFile);
    return 0;
}
