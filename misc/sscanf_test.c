#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  printf("\n");
  printf("Test case 1: 1 valid input\n");
  printf("--------------------------\n");
  char* teststr = "86";
  int testint = 0;
  int sscanout = sscanf(teststr,"%d",&testint);
  printf("sscanout: %d\n",sscanout);
  printf("testint: %d\n",testint);
  printf("\n");

  printf("Test case 2: 1 invalid input\n");
  printf("----------------------------\n");
  char* teststr1 = "ab";
  testint = 0;
  sscanout = sscanf(teststr1,"%d",&testint);
  printf("sscanout: %d\n",sscanout);
  printf("testint: %d\n",testint);
  printf("\n");

  printf("Test case 3: 2 valid inputs\n");
  printf("---------------------------\n");
  char* teststr2 = "86\t2565447";
  testint = 0;
  int testint2 = 0;
  sscanout = sscanf(teststr2,"%d\t%d",&testint,&testint2);
  printf("sscanout: %d\n",sscanout);
  printf("testint: %d\ntestint2: %d\n",testint,testint2);
  printf("\n");
  
  return 0;
}
