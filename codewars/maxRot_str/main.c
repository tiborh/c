#include <stdio.h>
#include <stdlib.h>
#include "maxRot.h" 

int main(int argc, char** argv) {
  if(argc > 1) {
    int num;
    sscanf(argv[1],"%d",&num);
    printf("%lld\n", maxRot(num));
  } else
    puts("A natural number is expected as an argument.");
  return EXIT_SUCCESS;
}

