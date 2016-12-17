/****************************************************************************
 * positive2.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demands that user provide a positive number.
 *
 * Demonstrates use of bool.
 ***************************************************************************/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // loop until user provides a positive integer
    bool thankful = false;
    do
    {
        printf("I demand that you give me a positive integer: ");
        if (GetInt() > 0)
            thankful = true;
    }
    while (thankful == false);
    printf("Thanks for the positive integer!\n");
    return 0;
}
