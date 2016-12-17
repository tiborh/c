#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINEWIDTH 1024
#define CODELENGTH 12
#define MAXLENGTH LINEWIDTH
#define TIMESTRLEN 16

int get_out_filename(char *);

int main(int argc, char **argv) {

  char out_filename[MAXLENGTH];
  int filenamelength=0;

  if((filenamelength = get_out_filename(out_filename)) == 0) {
    fprintf(stderr, "Failure to create output filename.\n");
    exit(EXIT_FAILURE);
  }

  printf("filenamelength: %d\n",filenamelength);

  return 0;
}

int get_out_filename(char *outname) {

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

  strcpy(outname,filenameprefx);
  strcat(outname,timestring);
  strcat(outname,extension);

  printf("The timestamp is: %s\n",timestring);
  printf("The output filename will be: %s\n",outname);

  if (!strlen(outname)) 
    return 0;
  else
    return (strlen(outname));
  
}
