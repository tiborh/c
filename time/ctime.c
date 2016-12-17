#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  long int inttimeval;
  char *pt_time;

  inttimeval = time(NULL);

  if(inttimeval == (time_t)-1) {
    printf("Time is unavailable.");
    exit(EXIT_FAILURE);
  }

  printf("Raw time is: %ld\n",inttimeval);

  pt_time = ctime(&inttimeval);

  printf("ctime representation of the same: %s\n",pt_time);

  return 0;
}
