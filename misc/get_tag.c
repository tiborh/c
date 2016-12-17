#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

int seek_tag(char *, char *);

int main(int argc, char *argv[])
{

  int cmp_res=0;

  if (argc < 3)
    {
      printf("Usage: %s input_file output_file\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  else
    {
      printf("Is the tag in the string? %d\n",seek_tag(argv[1],argv[2]));
    }


  exit(EXIT_SUCCESS);
}

int seek_tag(char *str1, char *str2)
{
  char *tag_start=NULL, *tag_end=NULL;
  int tag_length, i=0, is_tag=0;
  
  char the_tag[LINEWIDTH];
  

  tag_start = strchr(str1,'<');
  tag_end = strchr(str1,'>');

  /*tag_length = tag_end - tag_start;*/

  if (tag_start == NULL) return 0;
  if (tag_end == NULL) return 0;

  while(tag_start+i<=tag_end){
    the_tag[i] = *(tag_start+i++);
  }
  the_tag[i]='\0';

  puts(the_tag);

  if (strcmp(the_tag,str2)==0)
    is_tag=1;

  return is_tag;
}
