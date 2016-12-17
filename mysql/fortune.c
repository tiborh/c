#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{

  FILE *fp;
  char txt[1024];

  /* Open the command for reading. */
  char* command = "/usr/games/fortune";
  fp = popen(command, "r");
  if (fp == NULL) {
    fprintf(stderr,"Failed to run command: %s\n",command);
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(txt, sizeof(txt)-1, fp) != NULL) {
    printf("%s", txt);
  }

  /* close */
  pclose(fp);

  return 0;
}
