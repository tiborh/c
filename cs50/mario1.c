/* 
   mario.c draws half pyramid in terminal window 
   valid input values: 0 to 23
   invalid input value results in repeated reqest for input.
*/

#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 1024
#define FORMAT_STRING_LENGTH 32
#define PRINT_LENGTH 4
#define MAX_VALUE 23

int main(int argc, char **argv) {
  int input_value = -1; // should be invalid value if nothing is read
  char input_line[MAX_LENGTH]; // first, input is read to string

  /* Getting user input */
  if (argc > 1)
    sscanf(argv[1],"%d",&input_value);
  while (input_value < 0 || MAX_VALUE < input_value) {
    printf("height: ");
    fgets(input_line,MAX_LENGTH,stdin);
    sscanf(input_line,"%d",&input_value);
  }

  /* Building the pyramid */
  if (input_value > 0) { // if zero, there will be no printout
    char format_string[FORMAT_STRING_LENGTH] = "%";
    char string_length[PRINT_LENGTH] = ""; // length of string depends on number of layers

    /* constructing the format string for printf */
    if (input_value > 1) { // length is the matter only if there are at least 2 layers
      sprintf(string_length,"%d",input_value+1); // starts from 2, so each is 1 # longer
      strcat(format_string,string_length);
    }
    strcat(format_string,"s\n");

    /* printing the half pyramid line by line */
    char output_line[MAX_LENGTH + 1] = "#";
    for (int layer_count = input_value; layer_count >= 1; layer_count--) { // layer loop
      for (int i = 0; i < input_value - layer_count +1; i++) // line construction
	strcat(output_line,"#");
      printf(format_string,output_line);
      strcpy(output_line,"#");
    }

  }

  return 0;
}
