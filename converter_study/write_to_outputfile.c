#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINEWIDTH 1024
#define CODELENGTH 12
#define MAXLENGTH LINEWIDTH
#define TIMESTRLEN 16

int get_out_filename(char *);
int write_head(char *,char *);

int main(int argc, char **argv) {

  char out_filename[MAXLENGTH];
  char *xmlhead = "file_head.txt";

  if(!get_out_filename(out_filename)) {
    fprintf(stderr, "Failure to create output filename.\n");
    exit(EXIT_FAILURE);
  }

  if(!write_head(xmlhead,out_filename)) {
    fprintf(stderr, "Failure to write head.\n");
    exit(EXIT_FAILURE);
  }
    
  printf("%s -> %s\n",xmlhead,out_filename);

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

int write_head(char *inname, char *outname) {
  
  FILE *fpt_infile,*fpt_outfile;
  char str_tmp[LINEWIDTH];
  
  if((fpt_infile = fopen(inname,"r"))==(FILE *)NULL) {
    fprintf(stderr, "Cannot open file: %s.\n",inname);
    return 0;
  }

  if((fpt_outfile = fopen(outname,"w"))==(FILE *)NULL) {
    fprintf(stderr, "Cannot open file: %s.\n",outname);
    return 0;
  }

  while(fgets(str_tmp,LINEWIDTH,fpt_infile))
    fputs(str_tmp,fpt_outfile);

  fclose(fpt_outfile);
  fclose(fpt_infile);

  return 1;
}
