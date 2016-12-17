#include <stdio.h>

int main(int argc, char **argv) {
  int coins[] = {.25, .1, .05, .01};

  printf("Size of coins[]: %ld bytes\n",sizeof(coins));
  printf("Size of int: %ld bytes\n",sizeof(int));
  printf("Number of elements in coins[]: %ld / %ld = %ld\n",sizeof(coins),sizeof(int),sizeof(coins)/sizeof(int));
