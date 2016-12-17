//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define REQARGS 1

bool validate(char* data)
{
    if(data[0] == 's' &&
       data[1] == 't' &&
       data[2] == 'a' &&
       data[3] == 'r' &&
       data[4] == 't' &&
       data[5] == 'd' &&
       data[6] == 'a' &&
       data[7] == 'y' &&
       data[8] == '=' &&
       isdigit(data[9]) &&
       isdigit(data[10]) &&
       isdigit(data[11]) &&
       isdigit(data[12]) &&
       data[13] == '-' &&
       isdigit(data[14]) &&
       isdigit(data[15]) &&
       data[16] == '-' &&
       isdigit(data[17]) &&
       isdigit(data[18]) &&
       data[19] == '&' &&
       data[20] == 'e' &&
       data[21] == 'n' &&
       data[22] == 'd' &&
       data[23] == 'd' &&
       data[24] == 'a' &&
       data[25] == 'y' &&
       data[26] == '=' &&
       isdigit(data[27]) &&
       isdigit(data[28]) &&
       isdigit(data[29]) &&
       isdigit(data[30]) &&
       data[31] == '-' &&
       isdigit(data[32]) &&
       isdigit(data[33]) &&
       data[34] == '-' &&
       isdigit(data[35]) &&
       isdigit(data[36])
       )
        return true;
    else
        return false;
}

int main(int argc, char** argv)
{
  bool isValid = false;

  if (argc != 2)
    printf("number of args: %d, but we need %d\n",argc,(int)REQARGS+1);
  else
    isValid = validate(argv[1]);

  printf("Arg 1 is %s\n",isValid ? "valid" : "invalid");

  return 0;
}
