#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include <stdbool.h>

/* int * get_ints(int argc, char** argv, int reqnum) */
/* { */
/*   int* return_vals = malloc (sizeof (int) * (reqnum)); */

/*   for (int i = 0; i < reqnum; i++) */
/*     if (argc > i) */
/*       sscanf(return_vals[i]...); */
      
/* } */
char* value_asker = "Give a value: ";

char* proc_input(myInput the_input)
{
  char* the_output = malloc (sizeof (char) * (MAX_INPUT_WIDTH+1));
  the_output[0] = '\0';

  bool input_validation = false; 
  the_output = get_string(the_input.num_of_args,the_input.args,the_input.nu_of_needed);
  //printf("the_output: '%s'\n",the_output);
  input_validation = check_DataType(the_output,the_input.type_of_needed,the_input.nu_of_needed);
  if (input_validation == false)
    {
      printf("input validation has failed, exiting...\n");
      exit(1);
    }
  //printf("the_output: '%s'\n",the_output);
  return the_output;
}

bool check_DataType(char* the_input, DatType datatype, int num_of_data)
{
  char input_copy[MAX_INPUT_WIDTH+1]; /* strtok proved to have a side effect */
  strcpy(input_copy,the_input);
  bool ret_bool = true;
  char* astr;
  astr = strtok(input_copy,TEXT_DELIM);
  for (int i = 0; i < num_of_data; i++)
    {
      int test_val = 0;
      switch (datatype)
	{
	case integer:
	  if (sscanf(astr,"%d",&test_val) == 0)
	    {
	      printf("invalid integer: %s\n",astr);
	      return false;
	    }
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
      astr = strtok(NULL,TEXT_DELIM);
    }
  return ret_bool;
}

char* get_string(int argc, char** argv, int reqnum)
{
  char* the_input = malloc (sizeof (char) * (MAX_INPUT_WIDTH+1));
  the_input[0] = '\0';

  
  if (argc > 1)
    strcpy(the_input,argv[1]);
  if (argc > 2 && reqnum > 1)
    for (int i = 2; i <= reqnum && i < argc; i++)
      {
	strcat(the_input,TEXT_DELIM);
	strcat(the_input,argv[i]);
      }

  if (argc-1 < reqnum)
    {
      printf("number of arguments:\n");
      printf("\texpected: %d\n",reqnum);
      printf("\treceived: %d\n",argc-1);
      if (argc > 1)
	strcat(the_input,TEXT_DELIM);
      strcat(the_input,get_input());
      for (int i = 1; i < reqnum - (argc-1); i++)
	{
	  strcat(the_input,TEXT_DELIM);
	  strcat(the_input,get_input());
	}
    }
  return the_input;
}

char* get_input()
{
  char* the_input = malloc (sizeof (char) * (MAX_INPUT_WIDTH+1));
  the_input[0] = '\0';
  
  printf(value_asker);
  fgets(the_input,MAX_INPUT_WIDTH,stdin);
  if (the_input[strlen(the_input)-1] == '\n')
    the_input[strlen(the_input)-1] = '\0';

  if (strlen(the_input) == 0)
    {
      printf("zero length string error\n");
      exit(1);
    }

  return the_input;
}

int get_int(int argc, char** argv)
{
  char* in_string = get_string(argc,argv,1);
  int the_number = 0;

  if (sscanf(in_string,"%d",&the_number) == -1)
    {
      printf("cannot turn your input into an integer, exiting...\n");
      exit(1);
    }

  return the_number;
}

long get_long(int argc, char** argv)
{
  char* in_string = get_string(argc,argv,1);
  long the_number = 0;

  if (sscanf(in_string,"%ld",&the_number) == -1)
    {
      printf("cannot turn your input into a long integer, exiting...\n");
      exit(1);
    }

  return the_number;
}

long long get_longlong(int argc, char** argv)
{
  char* in_string = get_string(argc,argv,1);
  long long the_number = 0;

  if (sscanf(in_string,"%lld",&the_number) == -1)
    {
      printf("cannot turn your input into a long long integer, exiting...\n");
      exit(1);
    }

  return the_number;
}

float get_float(int argc, char** argv)
{
  char* in_string = get_string(argc,argv,1);
  float the_number = 0;

  if (sscanf(in_string,"%f",&the_number) == -1)
    {
      printf("cannot turn your input into a floating point number, exiting...\n");
      exit(1);
    }

  return the_number;
}

double get_double(int argc, char** argv)
{
  char* in_string = get_string(argc,argv,1);
  double the_number = 0;

  if (sscanf(in_string,"%lf",&the_number) == -1)
    {
      printf("cannot turn your input into a double precision floating point number, exiting...\n");
      exit(1);
    }

  return the_number;
}

/* legacy */
long process_input(int argc, char** argv)
{
  return get_long(argc,argv);
}
