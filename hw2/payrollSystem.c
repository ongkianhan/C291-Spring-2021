/* This is the payroll system that will follow the instructions on canvas for hw2.
 *
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/

#include <stdio.h>

int main(void) {

    char input = 'a';
    int count = 0;
    int countA_S, countR_J_T, countH;   // total count for all payroll types
    int weekA_S, weekR_J_T, weekH;      // total weekly salary for all payroll types
    int monthA_S, monthR_J_T, monthH;   // total monthly salary for all payroll types
    int payrateA_S, payrateR_J_T, payrateH; //total payrate for all payroll types
    double monthSalaryA, weekSalaryA, hourlySalaryRateA;
    double monthSalaryS, weekSalaryS, hourlySalaryRateS, overtimeSalaryRatesS, thisMonthS, thisWeekS;
    double monthSalaryR, weekSalaryR, hourlySalaryRateR, thisMonthR, thisWeekR;
    double monthSalaryJ, weekSalaryJ, hourlySalaryRateJ, thisMonthJ, thisWeekJ;
    double monthSalaryT, weekSalaryT, hourlySalaryRateT, thisMonthT, thisWeekT;
    double weekSalaryH, monthSalaryH, hourlySalaryRateH, normalHoursH, otHoursH;
    double salary, otHours, numCourse, hourPay;
    double creditHours, extra, numHours;


    // outer loop to check if Q if entered
    // first inner loop to check for details


    while (input != 'Q') {
        printf("\n Welcome to the Payroll System! \n Pay codes: \tAdmin(A) \n\t\tStaff(S)\n\t\tRegular Faculty(R)\n\t\tAdjunct(J)\n\t\tTeaching Assistant(T)\n\t\tHourly Staff(H)\n ");
        // input parameters required for each character code
        do {
            printf("\n Please input a paycode. \n");
            scanf(" %c", &input);
            switch (input) {
                case 'A':
                    printf("\n Please input your annual salary: ");
                    scanf(" %lf", &salary);
                    monthSalaryA = salary / 12;
                    weekSalaryA = salary / 52;
                    hourlySalaryRateA = salary / (52 * 40);
                    countA_S++;
                    weekA_S += weekSalaryA;
                    monthA_S += monthSalaryA;
                    payrateA_S += hourlySalaryRateA;
                    break;
                case 'S':
                    printf("\n Please input your annual salary, and any hours of OT: ");
                    scanf(" %lf %lf", &salary, &otHours);
                    if (otHours > 10) {
                        printf("Too many hours of OT. Request denied.");
                        count--;
                        break;
                    }
                    monthSalaryS = salary / 12;
                    weekSalaryS = salary / 52;
                    hourlySalaryRateS = salary / (52 * 40);
                    overtimeSalaryRatesS = hourlySalaryRateS * (0.75);
                    thisMonthS = monthSalaryS + otHours * overtimeSalaryRatesS;
                    thisWeekS = weekSalaryS + (otHours / 4) * overtimeSalaryRatesS;
                    countA_S++;
                    weekA_S += weekSalaryS;
                    monthA_S += monthSalaryS;
                    payrateA_S += hourlySalaryRateS;
                    break;
                case 'R':
                    printf("\n Please input your annual salary, and any extra credit hours taught: ");
                    scanf(" %lf %lf", &salary, &creditHours);
                    if (creditHours > 3)
                        creditHours = 3;
                    monthSalaryR = salary / 10;
                    weekSalaryR = monthSalaryR / 4;
                    hourlySalaryRateR = weekSalaryR / 40;
                    thisMonthR = monthSalaryS + (8500 / (5 * 3)) * creditHours;
                    thisWeekR = weekSalaryS + ((8500 / (5 * 3)) * creditHours) / 4;
                    countR_J_T++;
                    weekR_J_T += weekSalaryR;
                    monthR_J_T += monthSalaryR;
                    payrateR_J_T += hourlySalaryRateR;
                    break;
                case 'J':
                    printf("\n Please input the number of credit hours, and any extra credit hours taught: ");
                    scanf(" %lf %lf", &creditHours, &extra);
                    if (extra != 3) {
                        printf("Error! Extra credit hours is not 3. Request denied.");
                        count--;
                        break;
                    }
                    monthSalaryJ = creditHours * (8500 / (5 * 3));
                    weekSalaryJ = monthSalaryJ / 4;
                    hourlySalaryRateJ = weekSalaryJ / (40);
                    thisMonthJ = monthSalaryJ + (8500 / 5);
                    thisWeekJ = thisMonthJ / 4;
                    countR_J_T++;
                    weekR_J_T += weekSalaryJ;
                    monthR_J_T += monthSalaryJ;
                    payrateR_J_T += hourlySalaryRateJ;
                    break;
                case 'T':
                    printf("\n Please input the number of courses, and any overtime hours: ");
                    scanf(" %lf %lf", &numCourse, &extra);
                    if (extra / (5 * 4) > 2) {
                        extra = 40;
                    }
                    monthSalaryT = (numCourse * 2500) / 5;
                    weekSalaryT = monthSalaryT / 4;
                    hourlySalaryRateT = weekSalaryT / 10;
                    thisMonthT = monthSalaryT + ((extra / 5) * hourlySalaryRateT);
                    thisWeekT = weekSalaryT + (extra / (5 * 4)) * hourlySalaryRateT;
                    countR_J_T++;
                    weekR_J_T += weekSalaryT;
                    monthR_J_T += monthSalaryT;
                    payrateR_J_T += hourlySalaryRateT;
                    break;
                case 'H':
                    printf("Please input your hourly pay, and your number of hours worked every week this month. ");
                    scanf(" %lf %lf", &hourPay, &numHours);
                    if (numHours >= 40)
                        numHours = 40;
                    if (numHours > 20) {
                        otHoursH = numHours - 20;
                        normalHoursH = 20;
                    } else {
                        normalHoursH = numHours;
                    }

                    weekSalaryH = numHours * hourPay + otHoursH * 1.5 * hourPay;
                    monthSalaryH = weekSalaryH * 4;
                    hourlySalaryRateH = hourPay;
                    countH++;
                    weekH += weekSalaryH;
                    monthH += monthSalaryH;
                    payrateH += hourlySalaryRateH;
                    break;
            }

            ++count;
        } while (count < 6);

        do {
            printf("\n Welcome back to the menu. If you want to quit, enter 'Q'. If you want to restart, enter 'M'. Else, please type in a pay code to view the information. \n Pay codes: \tAdmin(A) \n\t\tStaff(S)\n\t\tRegular Faculty(R)\n\t\tAdjunct(J)\n\t\tTeaching Assistant(T)\n\t\tHourly Staff(H)\n\t\tQuit(Q) \n Enter your choice:\n");
            scanf(" %c", &input);

            switch (input) {

                case 'A':
                    printf("\n Your weekly salary received is %lf\n", weekSalaryA);
                    printf("\n Your monthly salary received is %lf\n", monthSalaryA);
                    printf("\n Your hourly salary rate is %lf\n", hourlySalaryRateA);

                    break;
                case 'S':
                    printf("\n Your weekly salary received is %lf\n", thisWeekS);
                    printf("\n Your monthly salary received is %lf\n", thisMonthS);
                    printf("\n Your hourly salary rate is %lf\n", hourlySalaryRateS);
                    break;
                case 'R':
                    printf("\n Your weekly salary received is %lf\n", thisWeekR);
                    printf("\n Your monthly salary received is %lf\n", thisMonthR);
                    printf("\n Your hourly salary rate is %lf\n", hourlySalaryRateR);
                    break;
                case 'J':
                    printf("\n Your weekly salary received is %lf\n", thisWeekJ);
                    printf("\n Your monthly salary received is %lf\n", thisMonthJ);
                    printf("\n Your hourly salary rate is %lf\n", hourlySalaryRateJ);
                    break;
                case 'T':
                    printf("\n Your weekly salary received is %lf\n", thisWeekT);
                    printf("\n Your monthly salary received is %lf\n", thisMonthT);
                    printf("\n Your hourly salary rate is %lf\n", hourlySalaryRateT);
                    break;
                case 'H':
                    printf("\n Your weekly salary received is %lf\n", weekSalaryH);
                    printf("\n Your monthly salary received is %lf\n", monthSalaryH);
                    printf("\n Your hourly salary rate is %lf\n", hourlySalaryRateH);
                    break;
                case 'M':
                    count = 0;
                    break;
                case 'Q':
                    printf("\n Here are the statistics for all three types of employees: \n");
                    printf("\n Administrators and Staff (A, S):\n");
                    printf("\n Average weekly salary: %lf", weekA_S / countA_S);
                    printf("\n Average monthly salary: %lf", monthA_S / countA_S);
                    printf("\n Average pay rate: %lf", payrateA_S / countA_S);

                    printf("\n Faculty (R, J, T):\n");
                    printf("\n Average weekly salary: %lf", weekR_J_T / countR_J_T);
                    printf("\n Average monthly salary: %lf", monthR_J_T / countR_J_T);
                    printf("\n Average pay rate: %lf", payrateR_J_T / countR_J_T);

                    printf("\n Hourly workers (H):\n");
                    printf("\n Average weekly salary: %lf", weekH / countH);
                    printf("\n Average monthly salary: %lf", monthH / countH);
                    printf("\n Average pay rate: %lf", payrateH / countH);

                    printf("\n Thank you for using the program. Goodbye!");
                    break;
            }
        } while ( input != 'Q');


    }
    return (0);
}