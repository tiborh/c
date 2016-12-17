#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  int int_isdst,int_tmp;
  time_t timesecs;
  struct tm *tm_struct;
  char *days[] = {"Sunday",
		  "Monday",
		  "Tuesday",
		  "Wednesday",
		  "Thursday",
		  "Friday",
		  "Saturday"};
  char *months[] = {"January",
		    "February",
		    "March",
		    "April",
		    "May",
		    "June",
		    "July",
		    "August",
		    "September",
		    "October",
		    "November",
		    "December"};
  char *pt_isdst[] = {"daylight saving time is not in effect.",
		      "daylight saving time is in effect.",
		      "daylight savint information is not available."};

  timesecs = time(NULL);

  if(timesecs == (time_t)-1) {
    printf("Time is unavailable.");
    exit(EXIT_FAILURE);
  }

  tm_struct = localtime(&timesecs);

  printf("tm_year : %d, so the year is: %d\n",tm_struct->tm_year,tm_struct->tm_year+1900);
  printf("tm_mon  : %d, so it is %s.\n",tm_struct->tm_mon,*(months+tm_struct->tm_mon));
  printf("tm_mday : %d, which is the day of the month.\n",tm_struct->tm_mday);
  printf("tm_hour : %d, which is the hour.\n",tm_struct->tm_hour);
  printf("tm_min  : %d, which is the minute.\n",tm_struct->tm_min);
  printf("tm_sec  : %d, which is the second.\n",tm_struct->tm_sec);
  printf("tm_wday : %d, so it is %s.\n",tm_struct->tm_wday,*(days+tm_struct->tm_wday));
  printf("tm_yday : %d, so it is the %d(st/nd/rd/th) day of the year.\n",tm_struct->tm_yday,tm_struct->tm_yday+1);
  int_tmp = tm_struct->tm_isdst;
  if(int_tmp == 0) int_isdst = 0;
  if(int_tmp > 0) int_isdst = 1;
  if(int_tmp < 0) int_isdst = 2;
  printf("tm_isdst: %d, so %s\n",int_tmp,*(pt_isdst+int_isdst));

  return 0;
}
