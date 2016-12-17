#include <stdio.h>

int main(int argc, char** argv)
{
  int a[][4] = {{0,1,2,3},
		{4,5,6,7},
		{8,9,0,1}};
  int (*p)[4] = a;		/* pointer to an array of four ints */
  size_t nrows = sizeof a / sizeof a[0];
  size_t ncols = sizeof a[0] / sizeof a[0][0];
  
  printf("size of the array: %d\n",sizeof a);
  printf("size of the zeroeth row: %d\n",sizeof a[0]);
  printf("so the number of rows: %d / %d == %d\n",sizeof a, sizeof a[0], sizeof a / sizeof a[0]); 
  printf("size of the zeroeth element: %d\n",sizeof a[0][0]);
  printf("so the number of cols: %d / %d == %d\n",sizeof a[0], sizeof a[0][0], sizeof a[0] / sizeof a[0][0]);

  printf("sizeof '(*p)': %d (which is the size of the row)\n",sizeof *p);
  for (int i = 0; i < nrows; i++)
    {
      for (int j = 0; j < ncols; j++)
	printf("%d ",p[i][j]);
      putchar('\n');
    }

  return 0;
}
