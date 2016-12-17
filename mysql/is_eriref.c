//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
#include <stdbool.h>
//#include <stdlib.h>
#include <string.h>
//#include <time.h>
//#include <math.h>
#include <ctype.h>

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

int main(int argc, char** argv)
{
  char* test_set[] = {"HS12623","hs12603","zz00001","hs00000","","A2","1234567","hsa1234","h123456","hs123456"};

  printf("size of test_set: %ld\n",sizeof(test_set));
  printf("size of test_set[0]: %ld\n",sizeof(test_set[0]));
  int nu_of_elems = sizeof(test_set) / sizeof(test_set[0]);
  printf("number of elements: %d\n",nu_of_elems);
  for (int i=0; i < nu_of_elems; ++i)
    printf("%7s:\t%s\n",*(test_set+i),is_eriref(*(test_set+i)) ? "true" : "false");

  return 0;
}
