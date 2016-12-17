#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 256
#define PATTLENGTH MAXLENGTH/4
#define DEBUG 0

int strepl(char *,char *, char *);

int main(int argc, char **argv)
{
  char strinput[MAXLENGTH+1]={0};
  char str2search[PATTLENGTH+1]={0}, str2replace[PATTLENGTH+1]={0};

  if (argc > 3)
    {
      strcpy(strinput,argv[1]);
      strcpy(str2search,argv[2]);
      strcpy(str2replace,argv[3]);
      strinput[MAXLENGTH] = '\0';
      str2search[PATTLENGTH] = '\0';
      str2replace[PATTLENGTH] = '\0';
#if DEBUG == 1
      puts(strinput);
      puts(str2search);
      puts(str2replace);
#endif
    }
  else
    {
      printf("Usage: prog_name \"input_string\" \"search_string\" \"replacement_string\"\n");
      exit(1);
    }

  printf("Text before replacement: %s\n",strinput);
  if (strepl(strinput,str2search,str2replace) == 1)
  	printf("Search string not found in input string.\nNo replacement has been made.\n");
  printf("Text after replacement: %s\n",strinput);

  return 0;
}

int strepl(char *strin,char *strpat1, char *strpat2)
{
  char strtmp[MAXLENGTH];
  char *ptrstr, *ptrtmp;
  int i=0;

/* phase zero: 
   - pointers set to first char of the input string
   - temporary string is set to null string */
  ptrstr = ptrtmp = strin;
  strtmp[0] = '\0';

  /* if line is empty, stop. */
  if (strin[0] == '\0')
    return 1;

/* phase one:
   check if searched pattern can be found in string */
  if ((ptrstr = strstr(strin,strpat1)) != NULL)
    {
/* phase two:
   check if the pattern is in front position */
      if (strin != ptrstr)
	{
/* phase three:
   if not, copy text before the pattern into temp string */
	  ptrtmp = strin;
	  do
	    strtmp[i++] = *ptrtmp;
	  while(++ptrtmp != ptrstr);
	  strtmp[i] = '\0';
	  printf("Before the pattern: %s\n",strtmp);
	}
/* phase four: 
   put the replacement pattern into temp string */
      strcat(strtmp,strpat2);
      printf("After providing the replacement: %s\n",strtmp);
      ptrtmp+=strlen(strpat1);
/* phases five and six:
   - check if there's any text after the pattern
   - if so, concatenate it to the temp string */
      if (*strtmp != '\0')
	strcat(strtmp,ptrtmp);
/* step seven:
   copy the assembled text into the original array, replacing the original string */
      printf("replaced text inside function: %s\n", strtmp);
      strcpy(strin,strtmp);
    }
  else
    {
      /* return 1 if pattern is not in text */
      return 1;
    }

  /* return 0 if replacement has been successful */
  return 0;
}
