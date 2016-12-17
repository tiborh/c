#include <stdio.h>
#include <math.h>

int main (int argc, char** argv)
{
  if (argc < 2)
    printf("Give a positive number as argument.\n");
  else
    {
      double the_number;
      sscanf(argv[1],"%lf",&the_number);
      //printf("The radical: %lf\n",the_number);
      double the_root = sqrt(the_number);
      printf("Square root of %lf is %lf\n", the_number, the_root );
    }
   
   return(0);
}

