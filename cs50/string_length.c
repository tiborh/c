/* 
   re-implementing strlen
 */

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

int string_length(char *the_string) {
  int length = 0;

  while (the_string[length] != '\0' && the_string[length] != '\n')
    length++;
  
  return length;
}

int main(int argc, char **argv) {
  char input_line[MAX_LENGTH];
  char *insert_txt = NULL;

  /* Getting user input */
  if (argc > 1) {
    strncpy(input_line,argv[1],MAX_LENGTH-1);
    insert_txt = "first argument";
  }
  else {
    printf("input string: ");
    fgets(input_line,MAX_LENGTH-1,stdin);
    insert_txt = "input";
  }

  printf("The length of your %s: %d\n",insert_txt,string_length(input_line));

  return 0;
}
