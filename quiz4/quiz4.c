#include <stdio.h>

int convertBinary(int input);


int convertBinary(int input)
{
    if ( input >> 1)
    {
        convertBinary(input >> 1);
    }
    printf("%c", (input & 1) ? '1' : '0');
    return 0;
}


int main(void) {


    printf("100 in binary: ");          // 3a) 100 decimal to binary, hexadecimal and octal
    convertBinary(100);
    printf(",hexadecimal:%#x  ,and octal: %#o\n",100,100);
    printf("12A in binary: ");          // 3b) 12A hex to binary, decimal and octal, 12A = 298
    convertBinary(298);
    printf(", decimal:%d  ,and octal: %#o\n",298,298);
    printf("701 octal in binary: ");    // 3c) 701 octal to binary, decimal and hex, 701 = 449
    convertBinary(449);
    printf(", decimal:%d  ,and hex: %#X\n",449,449);

    printf("\nQuestion 4a) Binary Numbers: A=00011100, B=01111111. \n");
    printf("A + B = ");             // A + B = 155
    convertBinary(155);
    printf("\n");
    printf("B - A = ");            // B - A = 99
    convertBinary(99);
    printf("\n");
    printf("A * B = ");            // A * B = 3556
    convertBinary(3556);
    printf("\n");

    printf("\nQuestion 4b) Octal Numbers: A= 1754, B=10001. \n");
    printf("A + B = %o",5101);             // A + B = 5101
    printf("\n");
    printf("B - A = %o", 3093);            // B - A = 3093
    printf("\n");
    printf("A * B = %o", 4113388);         // A * B = 4,113,388
    printf("\n");

    printf("\nQuestion 4c) Hexadecimal Numbers: A=100A1, B=B1100. \n");
    printf("A + B = %x",790945);             // A + B = 790,945
    printf("\n");
    printf("B - A = %x", 659551);            // B - A = 659,551
    printf("\n");
    printf("A * B = %x", 47646617856);         // A * B = 47,646,617,856
    printf("\n");

    return 0;
}
