#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

long long int factorial(short int );

int main(int argc, char **argv) {
  short int input_value = -1; // should be invalid value if nothing is read
  char input_line[MAX_LENGTH]; // first, input is read to string

  /* Getting user input */
  if (argc > 1)
    sscanf(argv[1],"%hd",&input_value);
  while (input_value < 0 || input_value > 44) {
    printf("Give me a non-negative integer between 0 and 44: ");
    fgets(input_line,MAX_LENGTH,stdin);
    sscanf(input_line,"%hd",&input_value);
  }

  printf("The factorial of %hd is %lld.\n",input_value,factorial(input_value));

  return 0;
}

long long int factorial(short int input_num) {

  if (input_num == 0)
    return 1;
  else
    return(input_num * factorial(input_num - 1));
}
