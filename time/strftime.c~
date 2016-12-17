#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  time_t timesecs;
  struct tm *tm_struct;
  char *pt_time;

  timesecs = time(NULL);

  if(timesecs == (time_t)-1) {
    printf("Time is unavailable.");
    exit(EXIT_FAILURE);
  }

  tm_struct = localtime(&timesecs);

  pt_time = asctime(tm_struct);

  printf("asctime representation of tm struct: %s",pt_time);

  if ((tm_struct = gmtime(&timesecs)) == NULL)
    printf("UTC time is not available");
  else
    printf("UTC time is: %s",asctime(tm_struct));

  return 0;
}
