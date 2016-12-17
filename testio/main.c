#include <stdio.h>
#include "testio.h"

int main()
{
    char* fn = "input.txt";

    writer(fn);
    processor(fn);
    return 0;
}
