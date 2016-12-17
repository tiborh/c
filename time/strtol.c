#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main(int argc, char **argv) {

  char *pt_temp;
  long int intput;
  short int i;

  if (argc < 2) {
    printf("Usage: you at least one argument string.\n");
    exit(EXIT_FAILURE);
  }
  for(i=1;i<argc;i++) {
    for(pt_temp=argv[i];*pt_temp!='\0' && isdigit(*pt_temp)==0;pt_temp++);
    printf("The number parsed: %ld\n",strtol(pt_temp,NULL,10));
  }

#if DEBUG
  printf("String input: %s\n",argv[1]);
  printf("isdigit(*pt_temp): %d\n",isdigit(*pt_temp));
  printf("pt_temp: %c\n",*pt_temp);
#endif

  return 0;
}

/*    printf("String input: %s\n",argv[i]); */
