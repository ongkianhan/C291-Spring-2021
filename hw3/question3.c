/*
 *  Followed instructions for question 3 of assignment 3
 *  Created payroll system and printed output according to pdf instructions
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include "file1.c"
#include<time.h> // followed example online

int num_of_employees = 5;

double print_statement(int num_of_employees);


double print_statement(int num_of_employees)
{
    extern double fed_Withholding;
    extern double state_Withholding;
    extern double retirement_contribution;
    double monthly_sales = 0;
    int sales[5];
    int length_of_service[5]; // created two arrays to store the values of sales and length of service to refer to later. I only initialized it to 5 since the requirements are only 5, but it can be increased if there are more employees in the future
    srand(time(0)); // implemented srandom here to make it pseudorandom
    for ( int i = 0; i < num_of_employees; i++) // for loop to generate random sales and length of service, updates arrays and respective total variables accordingly.
    {
        int curr_sales;
        double service_length;
        curr_sales = rand() % (10000 + 1 - 1000) + 1000;
        service_length = rand() % (30 + 1 - 1) + 1;
        sales[i] = curr_sales;
        length_of_service[i] = service_length;
        monthly_sales += curr_sales;
    }
    double monthly_profit = monthly_sales*0.45;
    // start of printing of payroll system
    printf("\nMONTHLY STATEMENT\t(JANUARY 2021)\n%80s\n%80s\n%80s\n","Bloomington Skating Company","Bloomington, IN","Phone: (812)-855-0000");
    printf("MONTHLY SALES:   %.2f\n",monthly_sales);
    printf("MONTHLY PROFIT:  %.2f\n",monthly_profit);
    printf("===============================================================================\n");
    printf("%4s%16s%11s%12s%11s%9s%17s\n","Name","Commission","Bonus","Fed W.","ST W.","RT","NET PAY");
    printf("-------------------------------------------------------------------------------\n");
    double totalCom = 0, totalBonus = 0, totalFedW = 0, totalstW = 0, totalrT = 0, totalNetPay= 0; // for the total row summations
    for ( int j = 0; j < 5; j++) // for loop for each employee, each employee is defaulted to Mr. 'person'
    {
        char person = 'A' + j;
        double this_Sales = sales[j];
        double commission = this_Sales*0.125;
        totalCom += commission;
        double service = length_of_service[j];
        double total_bonus = (0.05 + ((service / 10) * 0.05) ) * monthly_profit;
        totalBonus += total_bonus;
        double payBeforeTaxes = commission + total_bonus;
        double fedW = payBeforeTaxes*fed_Withholding;
        totalFedW += fedW;
        double stW = payBeforeTaxes*state_Withholding;
        totalstW += stW;
        double rT = payBeforeTaxes*retirement_contribution;
        totalrT += rT;
        double payAfterTaxes = payBeforeTaxes-fedW-stW-rT;
        totalNetPay += payAfterTaxes;
        printf("Mr. %c%11.2f%16.2f%10.2f%12.2f%12.2f%13.2f\n", person, commission, total_bonus, fedW, stW, rT, payAfterTaxes);

    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Total%11.2f%16.2f%10.2f%12.2f%12.2f%13.2f\n",totalCom, totalBonus, totalFedW, totalstW, totalrT, totalNetPay);
    printf("-------------------------------------------------------------------------------\n");
    printf("Net Profit (Profit - Bonus): %.2f\n",monthly_profit - totalBonus);
    printf("John Doe, Branch Manager\n");
    return 0;
}
int main(void)
{
    num_of_employees = 5;
    print_statement(5);

    return 0;
}
