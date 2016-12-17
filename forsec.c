#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define MAX_HEAD_DEPTH 4

void print_flags(int *);
void zero_flags(int *,int);

int main(int argc, char **argv)
{
  short int i,j,k=0;
  char in_line[LINEWIDTH+1]="<chl1>";
/*   char *infile_name = "testsec.txt"; */
  int flags[MAX_HEAD_DEPTH+1]={0};
  char *test_array[] = {"<chl1>",
		       "<chl2>",
		       "<chl3>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl2>",
		       "<chl3>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl3>",
		       "<chl4>",
		       "<chl1>",
		       "<chl2>",
		       "<chl3>",
		       "<chl4>",
		       "<chl2>",
		       "<chl3>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>",
		       "<chl3>",
		       "<chl4>",
		       "<chl4>",
		       "<chl4>"};
 

  while(k <= 25) 		/* max 30 */
    {
      for (i=1,j=MAX_HEAD_DEPTH;i<=MAX_HEAD_DEPTH;i++,j--)
	{
	  in_line[4]=i+48;
	  if (strcmp(in_line,test_array[k]) == 0)
	    {
	      zero_flags(flags,i);
	      flags[i]=1;
	      printf("%s",in_line);
	      print_flags(flags);
	    }
	}
      k++;
    }
  i=1;
  flags[1]=1;
  zero_flags(flags,i);
  return 0;
}

void zero_flags(int *inarray,int i)
{
  char out_line[LINEWIDTH+1]="</chl1>";
  int j;

  for(j=MAX_HEAD_DEPTH;j>=i;j--)
    {
      if (*(inarray+j)==1)
	{
	  out_line[5]=j+48;
	  puts(out_line);
	}
      *(inarray+j)=0;
    }
}

void print_flags(int *inarray)
{
  int i;
  printf("(");
  for (i=1;i<=MAX_HEAD_DEPTH;i++)
    printf("%d",*(inarray+i));
  printf(")\n");
}
