#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 4

int main(int argc, char **argv)
{
  char *chapter = "<chl1>";
  size_t length = LENGTH;
  char searched = 'c';
  char clipped[LENGTH+1];

  clipped[LENGTH]='\0';

  printf("The whole string: %s\n",chapter);
  printf("Started from search char: %s\n",strchr(chapter,searched));
  printf("The clipped string: %s\n",strncpy(clipped,strchr(chapter,searched),length));
  printf("String length of clipped: %d\n",strlen(clipped));

  return 0;
}
