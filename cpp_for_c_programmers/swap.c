#include <stdio.h>
#include <stdlib.h>

#define N_NUMS 2
#define INPUT_LENGTH 12

void swap(int*, int*);
int* inputter(char*);

int main(int argc, char** argv) {
  int* numbers = inputter("Give me two integers: ");
  //int i = *(numbers);
  //int j = *(numbers+1);
  printf("i: %d, j: %d\n",*numbers,*(numbers+1));
  swap(numbers,numbers+1);
  puts("After swap.");
  printf("i: %d, j: %d\n",*numbers,*(numbers+1));
  free(numbers);
  
  return(0);
}

void swap(int* i, int* j) {
  int tmp = *i;
  *i = *j;
  *j = tmp;
}

int* inputter(char* asker) {
  char input_str[INPUT_LENGTH*2] = {};
  int *number = (int *)malloc(N_NUMS*sizeof(int));
  int readval = 0;

  while(readval < 2) {
    puts(asker);
    fgets(input_str,INPUT_LENGTH*2,stdin);
    readval = sscanf(input_str,"%d %d",number,number+1);
  }

  return(number);
}
