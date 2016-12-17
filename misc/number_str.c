#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply_by_10(int number)
{
  char stringstream[10];	/* a nice misleading name :) */
  stringstream[0] = '\0';
  
  sprintf(stringstream,"%d%c",number,'0');

  int outnum = 0;
  if (sscanf(stringstream,"%d",&outnum))
    return outnum;
  else				/* can it ever get here? */
    {
      fprintf(stderr,"No valid number.\n");
      exit(1);
    }
}

int main(int argc, char** argv)
{

  for (int i = 0; i < 11; i++)	/* -std=c99 */
    printf("%3d %4d\n",i,multiply_by_10(i));
  printf("%d\n",multiply_by_10(INT_MAX)); /* it does not die, just overflows */

  return 0;
}
