#include <stdio.h>

enum dat_type {integer, longint, longlong, floating, doublefloat, longdouble, string};
typedef enum dat_type DatType;

void print_DataType(DatType data)
{
  switch (data)
    {
    case integer:
      printf("type of argument(s) needed: int\n");
      break;
    case longint:
      printf("type of argument(s) needed: long int\n");
      break;
    case longlong:
      printf("type of argument(s) needed: long long int\n");
      break;
    case floating:
      printf("type of argument(s) needed: floating point\n");
      break;
    case doublefloat:
      printf("type of argument(s) needed: double floating point\n");
      break;
    case longdouble:
      printf("type of argument(s) needed: long double floating point\n");
      break;
    case string:
      printf("type of argument(s) needed: string\n");
      break;
    default:
      printf("Not yet implemented type.\n");
    }
}

/* structs could be embedded into each other */
struct Input {
  int num_of_args;
  char** args;
  int nu_of_needed;
  DatType type_of_needed;
};
typedef struct Input myInput;

int main(int argc, char **argv) {
  int needed_args = 2;
  myInput input = {argc, argv, needed_args, integer};
  
  printf("Size of DatType: %d\n",sizeof(DatType));
  
  if (input.num_of_args > 1)
    {
      for(int i = 1; i < input.num_of_args && i <= input.nu_of_needed; i++)
	{
	  printf("%s\n",input.args[i]);
	}
      //printf("type of argument(s) needed: %s\n",input.type_of_needed);
      print_DataType(input.type_of_needed);
      if (input.num_of_args-1 < input.nu_of_needed)
	printf("fewer arguments than needed (%d)\n",input.nu_of_needed);
      else if (input.num_of_args-1 > input.nu_of_needed)
	printf("more arguments than needed\n");
      else if (input.num_of_args-1 == input.nu_of_needed)
	printf("just the right number of arguments\n");
    }
  else
    printf("no argument\n");
  
}

