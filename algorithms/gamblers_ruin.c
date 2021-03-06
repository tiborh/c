#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0
#define RESULT_SIZE 5

void usage()
{
  printf("Usage:\n");
  printf("\t argv[1]: stake  (starting sum)\n");
  printf("\t argv[2]: goal   (how much to stop at)\n");
  printf("\t argv[3]: trials (how many times to try\n");
  printf("\t argv[4]: bet    (how much is the bet each time\n");
}

int* gamblers_ruin (long, long, long, int);
long average(long*, long);

int main(int argc, char** argv)
{
  if (argc < 5)
    usage();
  else
    {
      long stake;
      long goal;
      long trials;
      int bet;
      sscanf(argv[1],"%ld",&stake);
      sscanf(argv[2],"%ld",&goal);
      sscanf(argv[3],"%ld",&trials);
      sscanf(argv[4],"%d",&bet);
      if (stake <= 0 || goal <= 0 || trials <= 0)
	{
	  printf("The numbers are supposed to be a positive.\n");
	  exit(1);
	}
      int* results = gamblers_ruin(stake,goal,trials,bet);
      double average_wins = 100.0 * ((double)results[0] / (double)trials);
      printf("Wins:   %d (%6.2lf)\n",results[0],average_wins);
      printf("Losses: %d (%6.2lf)\n",results[1],100.0-average_wins);
      printf("Average number of rounds: %d\n",results[2]);
    }
    
  return 0;
}

int* gamblers_ruin(long stake, long goal, long trials, int bet)
{
  long wins = 0;
  long losses = 0;
  int* results = malloc (sizeof (long) * (RESULT_SIZE));
  long round_counters[trials];
  srand(time(NULL));
  for (int i = 0; i < trials; i++)
    {
      long round_counter = 0;
      long current_sum = stake;
      while (current_sum > 0 && current_sum < goal)
	{
	  (rand() % 2 == 0) ? (current_sum += bet) : (current_sum -= bet);
	  round_counter++;
	}
      round_counters[i] = round_counter;
      current_sum <= 0 ? losses++ : wins++;
    }
  results[0] = wins;
  results[1] = losses;
  results[2] = average(round_counters,trials);
  printf("unfinished program...\n");
  return results;
}

long average(long* counters, long length)
{
  long average = 0;
  long long sum = 0;
  for(int i = 0; i < length; i++)
    sum += counters[i];
  average = sum / length;
  return average;
}
