/****************************************************************************
 * global.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Increments variables.
 *
 * Demonstrates use of global variable and issue of scope.
 ***************************************************************************/

#include <stdio.h>

// global variable
int x;

// function prototype
void increment(void);

int main(void)
{
    printf("x is now %d\n", x);
    printf("Initializing...\n");
    x = 1;
    printf("Initialized!\n");
    printf("x is now %d\n", x);
    printf("Incrementing...\n");
    increment();
    printf("Incremented!\n");
    printf("x is now %d\n", x);
    return 0;
}

/**
 * Increments x.
 */
void increment(void)
{
    x++;
}
