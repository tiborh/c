#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int* get_numbers()
{
  int* numbers = NULL;
  FILE* input;
  char* filename = "addnumbers.txt";
  if (NULL == (input = fopen(filename,"r")))
    {
      printf("Cannot open '%s' for reading. (error number: %d) (%s)\n",filename,errno,strerror(errno));
      return numbers;
    }
  
  char* line = NULL;
  size_t len = 0;
  size_t read;
  
  numbers = malloc(100 * sizeof(int));
  int i = 1;
  while ((read = getline(&line, &len, input)) != -1 && i < 100) {
    //printf("Retrieved line of length %zu: ", read);
    //printf("%s", line);
    if (0 != sscanf(line,"%d\n",(numbers+i)))
      i++;
  }
  *numbers = i;
  
  if (NULL == numbers)
    printf("Nothing was read from the file. (%s)\n",filename);

  fclose(input);

  return numbers;
}

int main(int argc, char** argv)
{
  int* numbers = get_numbers();
  if (NULL == numbers)
    {
      puts("NULL was returned. Exiting...");
      exit(1);
    }
  
  puts("The numbers read:");
  int sum = 0;
  for (int i = 1; i < *numbers; i++)
    {
      printf("%d\n",*(numbers+i));
      sum += *(numbers+i);
    }

  printf("The sum of the numbers: %d\n",sum);

  return 0;
}
