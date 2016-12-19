#include <stdio.h>
#include <stdlib.h>

#define N_NUMS 2
#define INPUT_LENGTH 12

void swap_double(double*, double*);
double* inputter(char*);

int main(int argc, char** argv) {
  double* numbers = inputter("Give me two doubles: ");
  //int i = *(numbers);
  //int j = *(numbers+1);
  printf("i: %lf, j: %lf\n",*numbers,*(numbers+1));
  swap_double(numbers,numbers+1);
  puts("After swap.");
  printf("i: %lf, j: %lf\n",*numbers,*(numbers+1));
  free(numbers);
  
  return(0);
}

void swap_double(double* i, double* j) {
  double tmp = *i;
  *i = *j;
  *j = tmp;
}

double* inputter(char* asker) {
  char input_str[INPUT_LENGTH*2] = {};
  double *number = (double *)malloc(N_NUMS*sizeof(double));
  int readval = 0;

  while(readval < 2) {
    puts(asker);
    fgets(input_str,INPUT_LENGTH*2,stdin);
    readval = sscanf(input_str,"%lf %lf",number,number+1);
  }

  return(number);
}
