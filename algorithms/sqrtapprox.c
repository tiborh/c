#include <stdio.h>
#include <math.h>
#include "functions.h"

#define DEBUG 0

double mysqrt(double);

int main(int argc, char** argv)
{
  double the_number = get_double(argc,argv);
  printf("The square root estimation of %lf is %lf.\n",the_number,mysqrt(the_number));
  printf("Square root from math library: %lf\n",sqrt((double)the_number));

  return 0;
}

double mysqrt(double radical)
{
  double myradical = radical;
  double root = myradical;
  double tolerance = 1e-15;
  double mytolerance = tolerance * myradical;
  if (DEBUG > 0)
    {
      printf("Radical as float: %lf\n",myradical);
      printf("Tolerance = %e\n",mytolerance);
      printf("diff: %lf\n",fabs(root * root - myradical));
    }
  while(fabs(root * root - myradical) > mytolerance)
    {
      if (DEBUG > 0)
	printf("Estimate: %lf (difference %e)\n",root,root*root-myradical);
      root = (root + myradical / root) / 2.0;
    }

  return root;
}
