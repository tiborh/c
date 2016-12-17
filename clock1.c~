#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

clock_t start, end;

void signal_callback_handler(int signum)
{
   printf("Caught signal %d\n",signum);
   printf("end: %ld\n",(long)end);
   printf("%lfs has passed.\n",(double)(end-start)/CLOCKS_PER_SEC);
   puts("Zero because the sleep makes the clock sleep.");
   printf("There are %ld clock ticks in a second.\n",CLOCKS_PER_SEC);
   exit(signum);
}


int main(int argc, char** argv)
{
  signal(SIGINT, signal_callback_handler);
  bool ticktack = true;
  start = end = clock();
  printf("start: %ld\n",(long)start);
  long long counter = 0;
  while(0 == end - start)
    {
      if (ticktack)
	{
	  puts("tick");
	  ticktack = false;
	}
      else
	{
	  puts("tack");
	  ticktack = true;
	}
      //sleep(1);
      end = clock();
      counter++;
    }
  printf("%lld loop cyles for one clock tick\n",counter);

  return 0;
}
