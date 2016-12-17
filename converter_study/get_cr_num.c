#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 1024

int main(int argc, char **argv)
{
  char inputline[LINEWIDTH+1],tmpc1,tmpc2,tmpc3;
  int crnum=0;

  if(argc< 2) {
    printf("CR number not found as argument.\n");
    exit(EXIT_FAILURE);
  }

  /*
  printf("CR number: ");
  fgets(inputline,LINEWIDTH,stdin);

  printf("Read: '%s'",argv[1]);
  */
  
  sscanf(argv[1],"CR-%d",&crnum);
  if(crnum == 0)
    printf("unsuccessful CR number parse\n");
  else
    printf("The CR number: %d\n",crnum);

  return 0;
}
