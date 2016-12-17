#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXNUM 10

char* allocate_to_string(char* instr)
{
  char* outstr = malloc(strlen(instr) * sizeof(char) + 1);
  if (NULL == outstr)
    printf("Cannot reserve memory space for %s\n",instr);
  else
    strcpy(outstr,instr);
  return outstr;  
}

int main(int argc, char** argv)
{
  char** saved_addresses = malloc(MAXNUM * sizeof(char*));
  char* my_string = allocate_to_string("What's up?");
  saved_addresses[0] = my_string;
  printf("Address of my_string: %p\n",my_string);
  printf("Value of my_string: %s\n",my_string);
  my_string = allocate_to_string("Fine, thanks.");
  saved_addresses[1] = my_string;
  printf("Address of my_string: %p\n",my_string);
  printf("Value of my_string: %s\n",my_string);
  free(saved_addresses[0]);
  free(saved_addresses[1]);
  printf("Address of first saved address after freeing string space: %p\n",saved_addresses[0]);
  printf("Address of second saved address after freeing string space: %p\n",saved_addresses[1]);
  free(saved_addresses);

  return 0;
}
