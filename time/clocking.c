#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

int main(int argc, char **argv) {
  clock_t start,end;
  long long int hugenum=1;
  int i;

  start=clock();

#if DEBUG
  printf("size of 'long long int': %ld\n",sizeof(hugenum));
#endif

  for(i=1;i<1000000000;i++)
    hugenum+=1;
  
  printf("hugenum: %lld\n",hugenum);

  end = clock();

  printf("running time: %.2f seconds\n",(double)(end-start)/(double)(CLOCKS_PER_SEC));

  return 0;
}
