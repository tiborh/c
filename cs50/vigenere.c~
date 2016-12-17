/* 
   Caesar cypher as a week 2 assignment for CS50

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1024

int main(int argc, char **argv) {

  char input_line[MAX_LENGTH];// for the string to transform

  if (argc != 2) {// only one command line argument is accepted
    printf("Exactly one argument is required.\nThat argument must be a positive integer.\n");
    return 1;
  }

  int the_key = atoi(argv[1]);
  if (the_key < 1) {// a too large number return -1 in atoi
    printf("The key is either too large or is not a positive integer.\n");
    return 2;
  }

  /* printf("Enter your string:\n"); */
  fgets(input_line,MAX_LENGTH,stdin);
  for (int i = 0, n = strlen(input_line); i < n; i++) {// going character by character
    char the_char = input_line[i];
    int the_crypt = the_key % 26;
    int crypted_code = the_char + the_crypt;
    if (isalpha(the_char)) {// changed only if alphabetic
      if (islower(the_char)) {// codes for lower and upper characters are different
	if (crypted_code > 122)
	  crypted_code = crypted_code - 122 + 96;// wrapover for lowercase
      } else if (crypted_code > 90) 
	crypted_code = crypted_code - 90 + 64;// wrapover for uppercase
      putchar(crypted_code);// crypted character
    } else
      putchar(the_char);// original unchanged character
  }

  return 0;
}
