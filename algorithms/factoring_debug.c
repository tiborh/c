#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0
#define MAX_INPUT_WIDTH 81

long process_input(int,char**);

int main(int argc, char** argv)
{
  long the_number = process_input(argc,argv);
  if (DEBUG > 0)
    printf("Input number: %ld\n",the_number);

  for(long the_factor = 2; the_factor <= the_number / 2; the_factor++)
    {
      if (DEBUG > 0)
	printf("quotient: '%ld'\n",the_number/2);
      if (the_number % the_factor == 0)
	{
	  the_number /= the_factor;
	  printf("%ld ",the_factor);
	  the_factor = 1;
	}
      if (DEBUG > 0)
	printf("the number: %ld\n",the_number);
    }
  printf("%ld\n",the_number);

  return 0;
}

long process_input(int argc, char** argv)
{
  char in_string[MAX_INPUT_WIDTH];
  if (argc < 2)
    {
      printf("Give me an integer as an argument to factor.\n");
      fgets(in_string,MAX_INPUT_WIDTH,stdin);
      if (strlen(in_string) == 0)
	{
	  printf("zero length string error\n");
	  exit(1);
	}
      if (DEBUG > 0)
	{
	  printf("length of in_string: %ld\n",strlen(in_string));
	  printf("in_string: '%s'\n",in_string);
	}
    }
  else
    {
      strncpy(in_string,argv[1],MAX_INPUT_WIDTH);
    }

  long the_number = 0;
  if (sscanf(in_string,"%ld",&the_number) == -1)
    {
      printf("cannot turn your input into a number, exiting...\n");
      exit(1);
    }

  return the_number;
}
