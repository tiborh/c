#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINEWIDTH 81
#define MAXLINES 100

char** createRaggedArray();
void freeArray(char**);

int main(int argc, char** argv)
{
  char** lines;

  lines = createRaggedArray();

  for(int i = 0; i < MAXLINES && *(lines + i) != NULL; i++)
    printf("%s",*(lines + i));

  freeArray(lines);
  //puts("Still alive.");
  return 0;
}

char** createRaggedArray()
{
  char* line = malloc(MAXLINEWIDTH * sizeof(char));
  if (line == NULL)
    {
      puts("Line cannot be created, exiting...");
      exit(1);
    }
  char** lines = malloc(MAXLINES);
  if (lines == NULL)
    {
      puts("Lines cannot be created, exiting...");
      exit(1);
    }

  for(int n = 0; n < MAXLINES && fgets(line,MAXLINEWIDTH-1,stdin); n++)
    {
      if ((lines[n] = malloc(strlen(line) + 1)) == NULL)
	{
	  printf("malloc cannot allocate more memory. exiting...");
	  exit(1); 
	}
      strcpy(lines[n],line);
    }
  return lines;
}

void freeArray(char** inArray)
{
    for(int i = 0; i < MAXLINES && *(inArray + i) != NULL; i++)
      free(*(inArray + i));
    free(inArray);
}
