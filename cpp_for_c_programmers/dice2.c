#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIDES 6
#define N_DICE 2
#define R_SIDE (rand() % SIDES + 1)
#define INPUT_LENGTH 12
#define VARIATIONS 64

int inputter(char* );

int main(int argc, char** argv) {
  srand(clock());

  int n_dice = inputter("\nNumber of dice: ");
  int trials = inputter("\nEnter number of trials: ");

  int outcomes[VARIATIONS] = {};

  for(int j=0;j<trials;++j) {
    int sidesum = 0;
    for(int k = 0; k < n_dice; ++k)
      sidesum += R_SIDE;
    outcomes[sidesum]++;
  }

  printf("probability:\n");
  for(int j=n_dice;j<n_dice*SIDES+1;++j)
    printf("j == %2d, p == %5.2lf%%\n",j,100*(double)(outcomes[j])/trials);

  return(0);
}

int inputter(char* asker) {
  puts(asker);

  char input_str[INPUT_LENGTH];
  fgets(input_str,INPUT_LENGTH,stdin);
  int number = 0;
  sscanf(input_str,"%d",&number);

  return(number);
}
