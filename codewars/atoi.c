#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv) {
  char one = '1';
  char one_str[2];
  sprintf(one_str,"%c",one);
  printf("one: %d\n",atoi(one_str));
  
  return EXIT_SUCCESS;
}
