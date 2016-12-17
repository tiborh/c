#include <stdio.h>
#include <string.h>

#define LINEWIDTH 1024
#define WORDLENGTH 24
#define MAXELEM 24

int linearSearch(const char **array, char *key, int size);
int getTag(const char in_string[]);

int main(int argc, char **argv)
{
  char in_str[LINEWIDTH];
  int taglength=0;

  printf("give me the line\n");
  fgets(in_str,LINEWIDTH,stdin);

  puts(in_str);

  if ((taglength=getTag(in_str))==-1)
    printf("Tag not found\n");
  else
    printf("Tag length: %d\n",taglength);

  return 0;
}

/* Extracts the (first) tag name from the string if it exists. */
int getTag(const char in_string[LINEWIDTH])
{
  char *pt_start, *pt_end, *pt_tmp;
  char str_tmp[LINEWIDTH/4];
  int i=0;

  if ((pt_start = strchr(in_string,'<')) == NULL)
  {
    return -1;
  }
  else if((pt_end = strchr(in_string,'>')) == NULL)
    {
      return -2;
    }
  else
    {
      pt_tmp = pt_start;
      pt_tmp++;
      do{
	str_tmp[i]=*(pt_tmp+i);
	i++;
      }while((pt_tmp+i)!=pt_end);
      str_tmp[i]='\0';
      printf("The tag: %s.\n",str_tmp);
      return(strlen(str_tmp));
    }

  return -3;
}

int linearSearch(const char **array, char *key, int size )
{
   int i;
   for ( i = 0; i < size; ++i ) {
     if ( strstr(array[i],key) != NULL ) {
       return i;
      }
   }
   return -1;

}
