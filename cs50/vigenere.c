/* 
   Vigenere cypher as a week 2 assignment for CS50

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1024

char *test_input_string(char *);

int main(int argc, char **argv) {

  char input_line[MAX_LENGTH];// for the string to be transformed

  if (argc != 2) {// only one command line argument is accepted
    printf("Exactly one argument is required.\nThat argument must be a string made up of alphabetic characters ([a-z][A-Z]).\n");
    return 1;
  }

  char *the_key = test_input_string(argv[1]);//see if key satisfies requirements
  if (the_key == NULL) {
    printf("The argument had non-alphabetic character(s).\n");
    return 1;
  }
  int key_length = (int)strlen(the_key);
  char current_key = *the_key;//first element of the key
  int key_pointer = 1;//which character to point at in key

  fgets(input_line,MAX_LENGTH,stdin);
  for (int i = 0, n = strlen(input_line); i < n; i++) {// going character by character
    char the_char = input_line[i];
    if (!isalpha(the_char)) {//non-alphabetic characters are not changed
      putchar(the_char);
      continue;
    }

    //how many characters to shift the character of the key by:
    int shift_char_by = islower(current_key) ? current_key - 97 : current_key - 65;
    int crypted_code = the_char + shift_char_by;
    
    if (islower(the_char)) {
      if (crypted_code > 122)
	crypted_code = crypted_code - 122 + 96;// wrapover for lowercase
    }
    else if (crypted_code > 90)
      crypted_code = crypted_code - 90 + 64;// wrapover for uppercase
    
    putchar(crypted_code);

    if (key_pointer < key_length)//stepping pointer in key
      current_key = *(the_key + key_pointer++);
    else {//or wrapping over to first char in key
      current_key = *the_key;
      key_pointer = 1;
    }
}
  return 0;
}

char *test_input_string(char *input_string) {

  for(int i = 0, n = strlen(input_string); i < n; i++)
    if (!isalpha(*(input_string + i)))
      return NULL;

  return input_string;
}
