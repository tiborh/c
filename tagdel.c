#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define MAXLENGTH LINEWIDTH
#define DEBUG 0

int tag_del(char *, char *);
int filltmp(char *, char *, char *);
int strepl(char *,char *, char *); /* to replace bits of string 
				      (in_what, search_what, 
				      replace_it_with_what) */

int main(int argc, char *argv[])
{
  char str_input[LINEWIDTH+1];
  int str_res=-1;

  if (argc < 3)
    {
      printf("Usage: %s str_to_search_in tag_to_delete\n",argv[0]);
      exit(EXIT_FAILURE);
    }

  strcpy(str_input,argv[1]);
  str_res = tag_del(str_input,argv[2]);

  if (str_res >= 0)
    printf("String after deletion: %s\n",str_input);
  else
    printf("<%s> NOT found in '%s'\n",argv[2],argv[1]);

  exit(EXIT_SUCCESS);
}

/* Search and destroy tag2del in str_orig */
int tag_del(char *str_orig, char *tag2del)
{
  char  *str_start, *str_end;
  char str_searched[LINEWIDTH+1];
  char strtmp[LINEWIDTH+1];

  strtmp[0]='\0';
  str_searched[0]='<';
  str_searched[1]='\0';
  strcat(str_searched,tag2del);

  /* 1. Is searched string in the original string? */
  if((str_start = strstr(str_orig,str_searched)) == NULL)
    return -1;
  if ((str_end = strchr(str_start,'>')) == NULL)
    return 1;

  /* 2. get the tag from < to >...*/
  filltmp(strtmp,str_start,str_end);

  /* ... and store it in an char array */
  strcpy(str_searched,strtmp);

#if DEBUG == 1
  printf("str_start: %c\n",*str_start);
  printf("str_end: %c\n",*str_end);
  printf("assembled tag: |%s|\n",str_searched);
#endif

  strepl(str_orig,str_searched,"");

    return 0;
}

/* auxiliary function to get_strfromtag() to extract substring 
   between "start" and "end" pointers */
int filltmp(char *tmp, char *start, char *end)
{
  int j=0;

  do{
    tmp[j]=*(start+j);
    j++;
  }while((start+j) != end);
  tmp[j]=*end;
  tmp[j+1]='\0';

  return 0;
}

/* Limitation: looks for only the first occurrence of the pattern */
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
	}
/* phase four: 
   put the replacement pattern into temp string */
      strcat(strtmp,strpat2);
      ptrtmp+=strlen(strpat1);
/* phases five and six:
   - check if there's any text after the pattern
   - if so, concatenate it to the temp string */
      if (*strtmp != '\0')
	strcat(strtmp,ptrtmp);
/* step seven:
   copy the assembled text into the original array, replacing the original string */
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
