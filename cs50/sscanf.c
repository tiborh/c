/* 
   To examine the return values of sscanf

 */

#include <stdio.h>
#include <string.h>

#define NUM_OF_ARGS 256

int main(int argc, char **argv) {

  int the_args[NUM_OF_ARGS][2] = {{0}};

  if (argc > 1) {
    for(int i = 1; i < argc && argc < NUM_OF_ARGS; i++)
      the_args[i-1][1] = sscanf(argv[i], "%d", &the_args[i-1][0]);
  } else
    printf("No arguments have been provided.\n");

  printf( (argc == 2 ? "Argument read:\n" : "Arguments read:\n") );
  for (int i = 0; i < argc-1; i++) {
    printf("%d: ",i);
    if (the_args[i][1] == 0)
      printf("(no useful input)");
    else
      printf("%d",the_args[i][0]);
    // printf(" (%d)",the_args[i][1]);
    printf("\n");
  }

  return 0;
}
