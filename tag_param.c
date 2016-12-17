#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1024
#define LINEWIDTH MAXLENGTH+1
#define TAGLENGTH 16
#define PATTLENGTH MAXLENGTH/4
#define DEBUG 0

char *get_substr(char *, char *); /* 1. input_string 2. tag found; 
				     RETURNS: pointer to char after the tag in input_string */
int strepl(char *,char *, char *);  /* 1. input_string 2. string to search for 3. string to replace it to */

int main(int argc, char *argv[])
{
  char tag_txt[TAGLENGTH], tag_replacement[LINEWIDTH];
  char *ptr_tmp;

  ptr_tmp = argv[1];

  tag_txt[0]='\0';
  tag_replacement[0]='\0';

  if (argc < 3)
    {
      printf("Usage: %s \"str_to_search_in\" \"insertion\"\n",argv[0]);
      exit(EXIT_FAILURE);
    }

  while((ptr_tmp=get_substr(ptr_tmp,tag_txt)) != NULL)
    {
      printf("'%s' found in '%s'\n",tag_txt,argv[1]);
    }

  strcpy(tag_replacement,tag_txt);
  strcat(tag_replacement," \0");
  strcat(tag_replacement,argv[2]);
#if DEBUG==1
  printf("The last tag text: %s\n", tag_txt);
  printf("The tag text with insertion: %s\n", tag_replacement);
#endif

  exit(EXIT_SUCCESS);
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
