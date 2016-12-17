#include <stdio.h>

int main(int argc, char **argv) {
  int i;

  for (i = 0; i < 10; i++) { /* initial declaration is not allowed in C99 */
    printf("%d: Hello, world!\n",i);
  }
  return 0;
}
