#include <stdio.h>

int multiply(int a, char *b) {
  return(a * *b);
}

int main(int argc, char** argv) {
  int n = 5;
  char ch = 'c';

  printf("%d * %d == %d\n",n,ch,multiply(n,&ch));
  
}
