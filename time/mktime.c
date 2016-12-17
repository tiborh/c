#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATESTRLEN 64

int main(int argc, char **argv) {

  time_t timesecs=0,nowtime=0;
  struct tm tmstruct={0},*nowstruct={0};
  char datestring[DATESTRLEN],*pt_year,*pt_month,*pt_day;
  short int vflag=0;
  long int int_year=0,int_month=0,int_day=0;

  if((nowtime=time(NULL))==(time_t)-1)
    printf("Time cannot be read.\n");
  else {
    nowstruct = localtime(&nowtime);
    tmstruct.tm_hour=nowstruct->tm_hour;
    tmstruct.tm_min=nowstruct->tm_min;
    tmstruct.tm_sec=nowstruct->tm_sec;
  }

  do{
  printf("Enter a date (yyyy-mm-dd): ");
  fflush(stdout);
  if((fgets(datestring,DATESTRLEN,stdin))==NULL) {
    printf("Read error.\n");
    continue;
  }
  if((pt_year=strtok(datestring,".-/ "))==NULL){
    printf("year could not be read\n");
    continue;
  }
  if((int_year=strtol(pt_year,NULL,10))==0){
    printf("invalid year string.\n");
    continue;
  }
  if((pt_month=strtok(NULL,".-/ "))==NULL) {
    printf("month could not be read\n");
    continue;
  }
  if((int_month=strtol(pt_month,NULL,10))==0){
    printf("invalid month string.\n");
    continue;
  }
  if((pt_day=strtok(NULL,".\n "))==NULL) {
    printf("day could not be read\n");
    continue;
  }
  if((int_day=strtol(pt_day,NULL,10))==0){
    printf("invalid day string.\n");
    continue;
  }
  vflag=1;
  }while(!vflag);
  printf("Read: %s/%s/%s\n",pt_day,pt_month,pt_year);

  tmstruct.tm_year=int_year-1900;
  tmstruct.tm_mon=int_month-1;
  tmstruct.tm_mday=int_day;

  if((timesecs=mktime(&tmstruct))==(time_t)-1)
    printf("Invalid date.\n");
  printf("Converted time string: %s",ctime(&timesecs));

  return 0;
}
