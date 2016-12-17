#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 0
#define MAX_INPUT_WIDTH 81

long process_input(int,char**);
bool is_prime(long);

int main(int argc, char** argv)
{
  long prime_counter = process_input(argc,argv);
  long the_number = 2;

  while(prime_counter > 0)
    {
      if (is_prime(the_number))
	{
	  printf(" %ld",the_number);
	  prime_counter--;
	}
      the_number++;
    }
  printf("\n");
}

bool is_prime(long the_number)
{
  long saved_number = the_number;

  for(long the_factor = 2; the_factor <= the_number / 2; the_factor++)
    {
      if (the_number % the_factor == 0)
	{
	  the_number /= the_factor;
	  the_factor = 1;
	}
    }

  if (saved_number == the_number)
    return true;
  else
    return false;
}

long process_input(int argc, char** argv)
{
  char in_string[MAX_INPUT_WIDTH];
  if (argc < 2)
    {
      printf("Give the number of primes you need.\n");
      fgets(in_string,MAX_INPUT_WIDTH,stdin);
      if (strlen(in_string) == 0)
	{
	  printf("zero length string error\n");
	  exit(1);
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
