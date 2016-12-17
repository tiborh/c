#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1024
#define LINEWIDTH 256
#define DEBUG 0

int str_ins(char *, char *, size_t);
char *get_substr(char *, char *); /* 1. input_string 2. tag found; 
				     RETURNS: pointer to char after the tag in input_string */


int main(int argc, char **argv)
{
  char str_modified[LINEWIDTH+1];
  int pos=0;

  if (argc < 4)
    {
      printf("Usage: %s str_2_insert_into str_2b_inserted position_2_insert_2\n",argv[0]);
      exit(EXIT_FAILURE);
    }

  printf("first argument: '%s'\n",argv[1]);
  printf("insertion point: '%s'\n",argv[3]);
  strcpy(str_modified,argv[1]);

  sscanf(argv[3],"%d",&pos);
  str_ins(str_modified,argv[2],pos);
  printf("The new string: %s",str_modified);
  
  exit(EXIT_SUCCESS);
}

int str_ins(char *str_into, char *str_which, size_t inspos)
{
  char strtmp[LINEWIDTH];

  strtmp[0]='\0';
  strncpy(strtmp,str_into,inspos);
  strcat(strtmp,str_which);
  strcat(strtmp,(str_into+inspos));
  printf("assembled string: %s\n",strtmp);
  strcpy(str_into,strtmp);

  return 0;
}


char *get_substr(char *str1, char *str2)
{
  char  *str_start, *str_end;
  char str_tag[LINEWIDTH];
  int i=0;

  /* 1. get the the start and end of the tag */
  if ((str_start = strchr(str1,'<')) == NULL)
    return(NULL);
  if ((str_end = strchr(str1,'>')) == NULL)
      return(NULL);

  /* 2. skip < & > */
  str_start++;
  str_end--;

  /* 3. Copy tag text into str_tag */
  /* removed from condition:   && (*(str_start+i) != ' ') */
  while(str_start+i<=str_end){
    str_tag[i] = *(str_start+i);
    i++;
  }
  str_tag[i]='\0';
  
  /* 4. copy tag text into main()'s array */
  strcpy(str2,str_tag);

#if DEBUG==1
  printf("|%s|\n",str_tag);
  printf("End char: %c\n",*str_end);
#endif

  return str_end+2;
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
