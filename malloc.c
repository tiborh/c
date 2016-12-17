#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* makeArray(char* inString)
{
  char* outArray = malloc(sizeof(char) * strlen(inString));
  strcpy(outArray,inString);
  return outArray;
}

char* addToArray(char* inString, char* addition)
{
  /* previously, sizeof was used here, which is an obvious mistake as 
     the size of a pointer has nothing to do with the length of the string. */
  if (NULL == realloc(inString,strlen(inString)+strlen(addition)))
    {
      printf("Something bad has happened while reallocating memory.\nExiting...\n");
      exit(1);
    }
  strcat(inString,addition);
  return(inString);
}

int main(int argc, char** argv)
{
  char* testArray = makeArray("A test string.");
  puts(testArray);
  testArray[strlen(testArray)-1] = '!';
  puts(testArray);
  testArray = addToArray(testArray," Something.");
  puts(testArray);
  puts("Attempting to free memory:");
  free(testArray); 
  puts("Memory has been freed.");
  puts(testArray);		/* Do not do this! */

  return 0;
}
