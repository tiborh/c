/* 
   greedy.c gives how many coins the given value can be expressed in
   coins to be used: quarter, dime, nickel, penny
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_LENGTH 1024

float get_input (int, char **); // get input from user
int coin_calc (float ); // calculate how many are needed of each coin
void init_array(int [], int); // write 0's as values
int coin_sum(int [], int); // add the number of coins

bool verbose = false; // verbose mode also prints how many of each coin

int main(int argc, char **argv) {

  printf("%d\n",coin_calc(get_input(argc,argv)));

  return 0;
}

float get_input (int argc, char **argv) {
  float input_value = -1.0; // should be invalid value if nothing is read
  char input_line[MAX_LENGTH]; // first, input is read to string

  if (argc > 1) {
    if (strcmp(argv[1],"-v") == 0) {
      verbose = true;
      if (argc > 2) {
	sscanf(argv[2],"%f",&input_value); // the number is accepted as an argument
      }
    } else {
      sscanf(argv[1],"%f",&input_value);
    }
  }
  while (input_value < 0.0) { // only positive values are accepted
    printf("How much change is owed?\n");
    fgets(input_line,MAX_LENGTH,stdin);
    sscanf(input_line,"%f",&input_value);
  }

  return input_value;
}

int coin_calc (float sum) {
  float coins[] = {.25, .1, .05, .01};
  int size_of_coins = (int) (sizeof(coins)/sizeof(float)); // number of array elements
  int how_many_coins[size_of_coins]; // counters for elements of coins[]

  init_array(how_many_coins,size_of_coins);

  for (int i = 0; i < size_of_coins; i++) {
    how_many_coins[i] = (int) (sum / coins[i] +.01); //to round instead of truncate
    sum = sum - coins[i] * how_many_coins[i];
  }

  if (verbose) {
    for (int i = 0; i < size_of_coins; i++)
      printf("%4.2f: %d\n",coins[i],how_many_coins[i]);
  }

  if (verbose)
    printf("Number of coins: ");

  return coin_sum(how_many_coins,size_of_coins);
}

void init_array(int the_array[], int array_size) {

  for (int i = 0; i < array_size; i++)
    the_array[i] = 0;
  
  return;
}

int coin_sum(int the_coins[], int coins_size) {
  int num_of_coins = 0;

  for (int i = 0; i < coins_size; i++)
    num_of_coins += the_coins[i];

  return num_of_coins;
}
