#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

int summation(int );

int main(int argc, char **argv) {
  int input_value = -1; // should be invalid value if nothing is read
  char input_line[MAX_LENGTH]; // first, input is read to string

  /* Getting user input */
  if (argc > 1)
    sscanf(argv[1],"%d",&input_value);
  while (input_value < 0) {
    printf("Give me a positive integer: ");
    fgets(input_line,MAX_LENGTH,stdin);
    sscanf(input_line,"%d",&input_value);
  }

  printf("The summation of %d is %d.\n",input_value,summation(input_value));

  return 0;
}

int summation(int input_num) {
  
  if (input_num == 0)
    return 0;
  else
    return(input_num + summation(input_num - 1));

  return 0;
}
