/****************************************************************************
 * ascii2.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Displays the mapping between alphabetical ASCII characters and
 * their decimal equivalents.
 *
 * Demonstrates iteration with a char.
 ***************************************************************************/

#include <stdio.h>

int main(void)
{
    // display mapping for uppercase letters
    for (char c = 'A'; c <= 'Z'; c = (char) ((int) c + 1))
        printf("%c: %d\n", c, (int) c);
    return 0;
}
