#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

int main(int argc, char *argv[])
{

  int cmp_res=0;

  if (argc < 3)
    {
      printf("Usage: %s input_file output_file\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  else
    {
      cmp_res = strcmp(argv[1],argv[2]);
      printf("comparison result: %d\n",cmp_res);
    }


  exit(EXIT_SUCCESS);
}
