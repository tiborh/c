#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define DEBUG 0

int get_strfromtag(char *, char *, char *);
int filltmp(char *, char *, char *);

int main(int argc, char *argv[])
{
  char str_in_tag[LINEWIDTH+1];
  int str_res=-1;

  str_in_tag[0] = '\0';

  if (argc < 3)
    {
      printf("Usage: %s str_to_search_in str_to_search_for\n",argv[0]);
      exit(EXIT_FAILURE);
    }

/*   printf("argv[1]: %s\n",argv[1]); */
/*   printf("argv[2]: %s\n",argv[2]); */
  str_res = get_strfromtag(argv[1],argv[2],str_in_tag);

  if (str_res >= 0)
    {
      printf("<%s> found in '%s'\n",argv[2],argv[1]);
      if (str_res == 0)
	printf("The string in the tag: %s",str_in_tag);
    }
  else
    printf("<%s> NOT found in '%s'\n",argv[2],argv[1]);

  exit(EXIT_SUCCESS);
}

/* A function created to help extract a string attribute from tags */
int get_strfromtag(char *str_orig, char *tag2find, char *str_extracted)
{
  char  *str_start, *str_end;
  char str_searched[LINEWIDTH+1];
  char strtmp[LINEWIDTH+1];

  strtmp[0]='\0';
  str_searched[0]='<';
  str_searched[1]='\0';
  strcat(str_searched,tag2find);
  strcat(str_searched,"\0");
  str_extracted[0] = '\0';

  /* 1. Is searched string in the original string? */
  if((str_start = strstr(str_orig,str_searched)) == NULL)
    return -1;
  /* 2. Is the tag name followed by an attribute? 
     (empty space usually implies that). */
  if((str_start = strchr(str_start,' ')) == NULL)
    {    
      return 1;
    }
  if ((str_end = strchr(str_start,'>')) == NULL)
    return 2;

  /* 3. get the tag from < to >...*/
  filltmp(strtmp,str_start,str_end);

  /* ... and store it in an char array */
  strcat(str_searched,strtmp);

  /* 4. get the string attribute between the opening and closing 
     double quotes. */
  if ((str_start = strchr(str_searched,'"')) == NULL)
    return 3;
  str_start++;
  if ((str_end = strchr(str_start,'"')) == NULL)
    return 4;
  str_end--;

  filltmp(strtmp,str_start,str_end);

  /* and store it in a char array */
  strcpy(str_extracted,strtmp);

#if DEBUG == 1
  printf("str_end: %c\n",*str_end);
  printf("assembled tag: |%s|\n",str_searched);
#endif

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
