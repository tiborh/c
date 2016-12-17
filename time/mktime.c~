#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMESTRLEN 16

int main(int argc, char **argv) {

  time_t timesecs;
  struct tm *pt_tmstruct;
  char timestring[TIMESTRLEN];
  char *timestamp = "%Y%m%d_%H%M%S";
  char *filenameprefx = "output_";
  char *extension = ".xml";

  timesecs = time(NULL);

  if(timesecs == (time_t)-1) {
    printf("Time is unavailable.");
    exit(EXIT_FAILURE);
  }

  pt_tmstruct = localtime(&timesecs);

  if(strftime(timestring,TIMESTRLEN,timestamp,pt_tmstruct)==0) {
      printf("the 'timestring' is too short\n");
      exit(EXIT_FAILURE);
    }

    printf("The timestamp is: %s\n",timestring);
    printf("The output filename will be: %s%s%s\n",filenameprefx,timestring,extension);

  return 0;
}
