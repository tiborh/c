/****************************************************************************
 * buggy4.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Should increment a variable, but doesn't!
 * Can you find the bug?
 ***************************************************************************/

#include <stdio.h>

// function prototype
void increment(void);

int main(void)
{
    int x = 1;
    printf("x is now %d\n", x);
    printf("Incrementing...\n");
    increment();
    printf("Incremented!\n");
    printf("x is now %d\n", x);
    return 0;
}

/**
 * Tries to increment x.
 */
void increment(void)
{
    x++;
}
