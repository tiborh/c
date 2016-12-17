#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    for(int i =0; i < argc; i++)
    puts(argv[i]);
    return 0;
}

char* makeArray(char* inStr)
{
    char* outArray = malloc(sizeof(char) * strlen(inStr));
				return outArray;
}
