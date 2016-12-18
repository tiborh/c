#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIDES 6
#define N_DICE 2
#define R_SIDE (rand() % SIDES + 1)
#define INPUT_LENGTH 12
#define VARIATIONS 64

int main(int argc, char** argv) {
  srand(clock());

  printf("\nEnter number of trials: ");

  char input_str[INPUT_LENGTH];
  fgets(input_str,INPUT_LENGTH,stdin);
  int trials;
  sscanf(input_str,"%d",&trials);

  int outcomes[VARIATIONS] = {};

  int d1,d2;
  for(int j=0;j<trials;++j)
    outcomes[(d1 = R_SIDE) + (d2 = R_SIDE)]++;

  printf("probability:\n");
  for(int j=N_DICE;j<N_DICE*SIDES+1;++j)
    printf("j == %2d, p == %5.2lf%%\n",j,100*(double)(outcomes[j])/trials);

  return(0);
}
