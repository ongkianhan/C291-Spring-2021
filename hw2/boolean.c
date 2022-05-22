/* Print a table of values for some boolean functions. */
/* This is a modified version of the boolean.c file provided on canvas.
 *
 * Author: Kent Ong
 * Bloomington, IN
 * Spring 2021
 *
*/
#include <stdio.h>

int main(void)
{
   int   b1, b2, b3, b4;             // boolean variables
   int   cnt = 0;

   printf("\n%5s%5s%5s%5s%5s%11s%9s%9s%9s\n\n",   // headings
      "Cnt", "b1", "b2", "b3", "b4", "fct 1", "fct 2", "fct 3", "fct 4"); //fct = function
        /* fct 1 = b1 || b2 || b3 || b4,
         * fct 2 = !(!b1 || b2) && (!b3 || b4)
         * fct 3 = (!b1 || b2) && (b3 && !b4)
         fct 4 = !(b1 && b2) || (b3 || b4) */
   for (b1 = 0; b1 <= 1; ++b1)
      for (b2 = 0; b2 <= 1; ++b2)
         for (b3 = 0; b3 <= 1; ++b3)
            for (b4 = 0; b4 <= 1; ++b4)
                  printf("%5d%5d%5d%5d%5d%9d%9d%9d%9d\n",
                     ++cnt, b1, b2, b3, b4,
                     b1 || b2 || b3 || b4, !(!b1 || b2) && (!b3 || b4),
                         ((!b1 || b2) && (b3 && !b4)), !(b1 && b2) || (b3 || b4));
   putchar('\n');
   return 0;
}
