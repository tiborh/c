//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
//#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define DEBUG 0
#define MAXNUM 100
#define TRNUMLENGTH 7

bool is_eriref(char* sample)
{
  if (strlen(sample)!=7)
    return false;
  if (!isalpha(*sample))
    return false;
  if (!isalpha(*(sample+1)))
    return false;
  for (int i = 2; i < 7; ++i)
    if (!isdigit(*(sample+i)))
      return false;
  bool zeros = true;

  for (int i = 2; i < 7; ++i)
      if (*(sample+i)!='0')
	zeros = false;

  if (zeros == true)
    return false;

  return true;
}

char** tr_number_parser(char *inputstr)
{
  char** collector = malloc(MAXNUM * sizeof(char*));
  char* a_tr;

  int wordcount = 0;
  int lettercount = 0;
  char lettercollect[TRNUMLENGTH + 1] = {};
  for(int i = 0; i < strlen(inputstr); ++i)
    {
      if (DEBUG)
	putchar(inputstr[i]);
      if (!isalnum(inputstr[i]))
	{
	  lettercount = 0;
	  lettercollect[0] = '\0';
	  if (DEBUG)
	    puts(":(not alpha or num)");
	  continue;
	}
      lettercollect[lettercount] = inputstr[i];
      lettercollect[lettercount+1] = '\0';
      ++lettercount;
      if (DEBUG)
	{
	  printf("(collected: %s)",lettercollect);
	  putchar('\n');
	}
      if(strlen(lettercollect) == 7)
	{
	  if(is_eriref(lettercollect))
	    {
	      a_tr = malloc((TRNUMLENGTH + 1) * sizeof(char));
	      strcpy(a_tr,lettercollect);
	      collector[wordcount++] = a_tr;  
	    }
	  lettercollect[0] = '\0';
	  lettercount = 0;
	  continue;
	}
      if (wordcount > MAXNUM)
	break;
    }

  return collector;
}

int main(int argc, char** argv)
{
  //char* sample_input = "HT50001";
  char* sample_input = "'HT48010',\n alpha'HT50001',\n 'HT50002', 'HT60563', ooo'HT72445', 'HT72874', 'HT75999', 'HT77381'";
  char** the_trs = tr_number_parser(sample_input);

  printf("Test string: %s\n",sample_input);
  puts("\nTest output:");
  for(int i = 0; the_trs[i] != NULL; ++i)
    printf("%s\n",the_trs[i]);      

  for(int i = 0; the_trs[i] != NULL; ++i)
    free(the_trs[i]);
  free(the_trs);

  return 0;
}
