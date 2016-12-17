#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  long int inttimeval;

  inttimeval = time(NULL);

  if(inttimeval == (time_t)-1) {
    printf("Time is unavailable.");
    exit(EXIT_FAILURE);
  }

  printf("Raw time is: %ld\n",inttimeval);

  return 0;
}
