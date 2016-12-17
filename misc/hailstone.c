#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXINPUT 100

int check_if_numeric(char*, int);

int main(int argc, char** argv) {

  if (argc == 1)
    puts("You need a starting number.");

  for (int i=1; i < argc; ++i) {
    printf("%s",argv[i]);
    if (!check_if_numeric(argv[i],strlen(argv[i])))
      continue;
    int aVal = 0;
    sscanf(argv[i],"%d",&aVal);
    while(aVal != 1) {
      if (aVal % 2 == 0) {
	aVal /= 2;
      } else {
	aVal = 3 * aVal + 1;
      }
      printf(" %d",aVal);
    }
    printf("\n");
  }
  
  return(0);
}

int check_if_numeric(char* input, int length) {
  for (int i=0;i<length; i++)
    if (!isdigit(input[i]))
      {
	printf (" Input is not an integer\n");
	return(0);
      }
  
  return(1);
}
