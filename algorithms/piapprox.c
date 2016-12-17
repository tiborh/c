#include <stdio.h>
#include <math.h>
#include "functions.h"

#define MYPI 3.14159265358979323846

double piapprox1(long);
void print_results(double);

int main(int argc, char** argv)
{
  long pi_steps = process_input(argc,argv);
  double approximation = piapprox1(pi_steps);
  print_results(approximation);

  return 0;
}

double piapprox1(long pi_steps)
{
  double approximation = 0.0;
  double saved_approx = 0.0;

  for (long i = 1; i <= pi_steps; i++)
    {
      approximation += 1 / (1.0*i*i);
      /* if (approximation > 2.0) */
      /* 	{ */
      /* 	  printf("Overflow at i = %ld\n",i); */
      /* 	  printf("increment: %17.15lf\n",1.0 / (1.0*i*i)); */
      /* 	  approximation = saved_approx; */
      /* 	  break; */
      /* 	} */
      saved_approx = approximation;
    }
  return approximation;
}

void print_results(double approximation)
{
  double piapprox = sqrt(approximation*6);
  //printf("The approximate value: %lf\n", approximation);
  printf("Pi approximate value:\n%17.15lf\n", piapprox);
  printf("%17.15lf (MYPI)\n",MYPI);
  printf("Difference:\n%17.15lf\n",MYPI-piapprox);
}
