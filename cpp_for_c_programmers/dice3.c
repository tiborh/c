#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R_SIDE (rand() % n_sides + 1)
#define INPUT_LENGTH 12
#define VARIATIONS 64

int inputter(char* );

int main(int argc, char** argv) {
  srand(clock());

  int n_sides = inputter("\nNumber of sides: ");
  int n_dice = inputter("\nNumber of throwables: ");
  int trials = inputter("\nNumber of trials: ");

  int outcomes[VARIATIONS] = {};

  for(int j=0;j<trials;++j) {
    int sidesum = 0;
    for(int k = 0; k < n_dice; ++k)
      sidesum += R_SIDE;
    outcomes[sidesum]++;
  }

  printf("probability:\n");
  for(int j=n_dice;j<n_dice*n_sides+1;++j)
    printf("j == %2d, p == %5.2lf%%\n",j,100*(double)(outcomes[j])/trials);

  return(0);
}

int inputter(char* asker) {
  char input_str[INPUT_LENGTH] = {};
  int number = 0;
  int readval = 0;

  while(readval < 1) {
    puts(asker);
    fgets(input_str,INPUT_LENGTH,stdin);
    readval = sscanf(input_str,"%d",&number);
  }

  return(number);
}
