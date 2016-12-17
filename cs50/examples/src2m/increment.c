#include <stdio.h>

// prototype
int cube(int input);

int main(void)
{
    int x = 2;
    printf("x is %d\n", x);
    x = cube(x);
    printf("x is %d\n", x);
    return 0;
}

int cube(int input)
{
   int output = input * input * input;
   return output;
}
