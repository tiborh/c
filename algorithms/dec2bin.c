#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

char* dec2bin(long);

int main(int argc, char** argv)
{
  if (argc < 2)
    printf("Give me a positive integer as an argument.\n");
  else
    {
      long the_number;
      sscanf(argv[1],"%ld",&the_number);
      if (the_number <= 0)
	{
	  printf("The number is supposed to be a positive number.\n");
	  exit(1);
	}
      char* bin_representation = bin_representation = dec2bin(the_number);
      printf("The binary representation of %ld is %s (length: %d).\n",the_number,bin_representation,strlen(bin_representation));
    }
    
  return 0;
}

char* dec2bin(long in_num)
{
  long greatest2power = 1;
  int two_power = 0;

  while (greatest2power * 2 <= in_num)
    {
      greatest2power *= 2;
      two_power++;
    }

  if (DEBUG > 0)
    printf("Greatest power of two: %ld (2^%d)\n",greatest2power,two_power);

  long current2power = greatest2power;
  long current_in_number = in_num;
  char* bin_str = malloc (sizeof (char) * (two_power+2));
  int str_index = 0;

  while (current2power > 0)
    {
      if (current_in_number < current2power)
	{
	  if (DEBUG > 0)
	    putchar('0');
	  bin_str[str_index] = '0';
	}
      else if (current_in_number >= current2power)
	{
	  if (DEBUG > 0)
	    putchar('1');
	  current_in_number -= current2power;
	  bin_str[str_index] = '1';
	}
      current2power /= 2;
      str_index++;
    }
  bin_str[two_power+1] = '\0';
  if (DEBUG > 0)
    putchar('\n');

  return bin_str;
}
