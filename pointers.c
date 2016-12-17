#include <stdio.h>
#include <string.h>

void printString(char*);
void printString2(char*);

int main(int argc, char** argv)
{
  int i = 46;
  int* pi = &i;

  printf("The address %p points at %d.\n",pi,i);
  *pi = 8;
  printf("Now the address %p points at %d.\n",pi,i);
  int j = 23;
  pi = &j;
  printf("The address %p points at %d.\n",pi,*pi);

  printString("Sample string.");
  printString("Another sample string.");

  return 0;
}

void printString(char* inString)
{
  for (int i = 0; i < strlen(inString); i++)
    putchar(*(inString+i));
  putchar('\n');
}

void printString2(char* inString)
{
  int i = 0;
  while(*(inString + i) != '\0')
    putchar(*(inString+i++));
  putchar('\n');
}
