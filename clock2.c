#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

time_t start, end;

void signal_callback_handler(int signum)
{
   printf("Caught signal %d\n",signum);
   printf("end: %ld\n",(long)end);
   double time_difference = difftime(end,start);
   printf("%lfs has passed.\n",time_difference);
   exit(signum);
}


int main(int argc, char** argv)
{
  signal(SIGINT, signal_callback_handler);
  bool ticktack = true;
  start = end = time(NULL);
  printf("start: %ld\n",(long)start);
  //long long counter = 0;
  while(1)
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
      sleep(1);
      end = time(NULL);
      //counter++;
    }
  //printf("%lld loop cyles for one clock tick\n",counter);

  return 0;
}
