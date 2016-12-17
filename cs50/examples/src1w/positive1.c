/****************************************************************************
 * positive1.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demands that user provide a positive number.
 *
 * Demonstrates use of do-while.
 ***************************************************************************/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // loop until user provides a positive integer
    int n;
    do
    {
        printf("I demand that you give me a positive integer: ");
        n = GetInt();
    }
    while (n < 1);
    printf("Thanks for the %d!\n", n);
    return 0;
}
