#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int seconds = 101;

double give_average(long* diffs)
{
  long long sum = 0;
  for(int i = 1; i < seconds; i++)
    sum += (long long)diffs[i];
  return (double)sum/(seconds-1);
}

void print_clock_array(clock_t* clocks)
{
  long* diffs = malloc(seconds * sizeof(long));
  printf("%d: %lu\n",0,(unsigned long)clocks[0]);
  for(int i = 1; i <= seconds; i++)
    {
      long adiff = (long)(clocks[i]-clocks[i-1]);
      printf("%3d: %lu (diff: %ld)\n",i,(unsigned long)clocks[i],adiff);
      diffs[i-1] = adiff;
    }
  double avrg = give_average(diffs);
  free(diffs);
  printf("The average difference (skipping the first diff): %lf\n",avrg);
}

int main(int argc, char** argv)
{
  clock_t* clocks = malloc(seconds * sizeof(clock_t) + 1);
  time_t time_start = time(NULL);
  clock_t clock_start = clock();
  time_t curr_time = 0;
  clock_t curr_clock = 0;
  printf("running time will be %d seconds\n",seconds+1);
  clocks[0] = clock() - clock_start;
  for(int i = 1; i <= seconds; i++)
    {
      while(curr_time < i)
	{
	  curr_time = difftime(time(NULL),time_start);
	  curr_clock = clock() - clock_start;
	}
      clocks[i] = curr_clock;
    }

  print_clock_array(clocks);
  free(clocks);
  return 0;
}
