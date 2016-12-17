/* 
   testing argv
 */

#include <stdio.h>

int main (int argc, char **argv) {
  if (argc) {
    printf("argc: %d\n",argc);
    for (int i = 0; i < argc; i++)
      printf("argv[%d]: %s\n",i,argv[i]);
  }
}
