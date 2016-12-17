#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
  if (argc < 2)
    printf("Give me how many random numbers as argument.\n");
  else
    {
      int the_number;
      sscanf(argv[1],"%d",&the_number);
      srand(time(NULL));
      printf("RAND_MAX: %d\n",RAND_MAX);
      for (int i = 0; i < the_number; i++)
	printf("%d\n",rand());
    }
}
