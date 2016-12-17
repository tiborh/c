#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define TAGLENGTH 16

char *get_substr(char *, char *);

int main(int argc, char *argv[])
{
  char tag_txt[TAGLENGTH];
  char *ptr_tmp;

  ptr_tmp = argv[1];

  tag_txt[0]='\0';

  if (argc < 2)
    {
      printf("Usage: %s \"str_to_search_in\"\n",argv[0]);
      exit(EXIT_FAILURE);
    }

/*   printf("argv[1]: %s\n",argv[1]); */

  while((ptr_tmp=get_substr(ptr_tmp,tag_txt)) != NULL)
    {
      printf("'%s' found in '%s'\n",tag_txt,argv[1]);
      puts(ptr_tmp);
    }

  exit(EXIT_SUCCESS);
}

char *get_substr(char *str1, char *str2)
{
  char  *str_start, *str_end;
  char str_tag[LINEWIDTH], str_searched[LINEWIDTH+1];
  int i=0;

  str_searched[0]='<';
  str_searched[1]='\0';

  if ((str_start = strchr(str1,'<')) == NULL)
    {
      printf("tagstart not found\n");
      return(NULL);
    }
  if ((str_end = strchr(str1,'>')) == NULL)
    {
      printf("tagend not found\n");
      return(NULL);
    }

  str_start++;
  str_end--;

  /* removed from condition:   && (*(str_start+i) != ' ') */
  while(str_start+i<=str_end){
    str_tag[i] = *(str_start+i);
    i++;
  }
  str_tag[i]='\0';
  strcat(str_searched,str2);
  
  printf("|%s|\n",str_tag);
  strcpy(str2,str_tag);
  /*printf("End char: %c\n",*str_end);*/

  return str_end+2;
}
