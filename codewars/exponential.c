#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long expt(long long m, long long e) {
  if (e == 0)
    return 1;
  if (e == 1)
    return m;
  return(m * expt(m,e-1));
}

void test_expt(void) {
  assert(expt(2,1) == 2);
  assert(expt(2,2) == 4);
  assert(expt(1,10) == 1);
  assert(expt(2,3) == 8);
  puts("Tests have passed.");
}

int main(int argc, char** argv) {
  if(argc < 3) {
    test_expt();
    puts("Two natural numbers are expected.");
  } else {
    long long m,e;
    sscanf(argv[1],"%lld",&m);
    sscanf(argv[2],"%lld",&e);
    printf("%lld^%lld == %lld\n",m,e,expt(m,e));
  }
  
  return EXIT_SUCCESS;
}
