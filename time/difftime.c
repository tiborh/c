#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  time_t start,end;

  start = time(NULL);

  if(start == (time_t)-1) {
    printf("Time is unavailable.");
    exit(EXIT_FAILURE);
  }

  printf("After a few seconds, press ENTER.\n");
  fflush(stdout);

  getchar();

  end = time(NULL);
  printf("The intervall was %.2f seconds\n",difftime(end,start));

  return 0;
}
