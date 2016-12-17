#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIDES 6
#define N_DICE 2
#define OUTCOMES (SIDES * N_DICE)
#define R_SIDE (rand() % SIDES + 1)
#define LINELENGTH 80

int get_nu_of_trials(void)
{
  printf("\nEnter the number of trials: ");
  int trials = 0;
  char input_line[LINELENGTH + 1] = {0};
  if (NULL == fgets(input_line,LINELENGTH,stdin))
    return 0;
  sscanf(input_line,"%d",&trials);

  return trials;
}

int* make_trials(int trials)
{
  srand(clock());
  int* outcomes;
  if (NULL == (outcomes = malloc((OUTCOMES+1) * sizeof(int))))
    return NULL;
  int d1,d2; d1 = d2 = 0;
  for(int j = 0; j < trials; j++)
    outcomes[(d1 = R_SIDE) + (d2 = R_SIDE)]++;

  return outcomes;
}

void print_results(int trials, int* outcomes)
{
  puts("Probabilities:");
  for(int j = 2; j < OUTCOMES+1; j++)
    printf("j = %2d, p = %7.4lf %%\n",j,(double)(outcomes[j])/trials*100);
}

int main(int argc, char** argv)
{
  /* get input */
  int trials = 0;
  if (0 == (trials = get_nu_of_trials()))
    return 0;

  /* roll the dice */
  int* outcomes = make_trials(trials);
  if (NULL == outcomes)
    {
      puts("Cannot allocate enough space for outcomes. Exiting...");
      exit(1);
    }

  /* show results */
  print_results(trials,outcomes);

  /* cleanup */
  free(outcomes);

  return 0;
}

