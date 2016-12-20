#include <stdio.h>

int main() {
  printf("  3/4 with float: %f (with cast of first)\n",(double)3/4);
  printf("  3/4 with float: %f (with cast of result)\n",(double)(3/4));
  printf("  3/4 with int:   %d\n",3/4);
  printf("3.0/4 with float: %f\n",3.0/4);
  printf("3.0/4 with int:   %d (with cast of first)\n",(int)3.0/4);
  printf("3.0/4 with int:   %d (with cast of result)\n",(int)(3.0/4));
  
  return(0);
}
