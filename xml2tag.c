#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

int seek_tag(char *, char *);

int main(int argc, char *argv[])
{
  FILE *in_file, *out_file;
  char infile_name[LINEWIDTH], outfile_name[LINEWIDTH];
  char in_line[LINEWIDTH+1], *temp_char;

  if (argc < 3)
    {
      printf("Usage: %s input_file output_file\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  else
    {
      strcpy(infile_name,argv[1]);
      strcpy(outfile_name,argv[2]);
    }

  if ((in_file = fopen(infile_name, "r")) == (FILE *)NULL)
    {
      fprintf(stderr, "Cannot open %s.\n",infile_name);
      exit(EXIT_FAILURE);
    }

  if ((out_file = fopen(outfile_name, "w+")) == (FILE *)NULL)
    {
      fprintf(stderr, "Cannot open %s.\n",outfile_name);
      exit(EXIT_FAILURE);
    }


  while(fgets(in_line,sizeof(in_line)-1,in_file) != NULL)
    {
  
      if(seek_tag(in_line,"<entry>"))
	printf("%s",in_line);

      /*
      if(strstr(in_line,"backup") == NULL)
	{
	  if((temp_char=memchr(in_line,'*',strlen(in_line))) != NULL)
	    {
	      *temp_char='\n';
	      *(temp_char+1)='\0';
	    }
	  if((temp_char=memchr(in_line,'@',strlen(in_line))) != NULL)
	    {
	      *temp_char='\n';
	      *(temp_char+1)='\0';
	    }
	  fprintf(out_file,"%s",in_line);
	}
      */
    }


  if (fclose (out_file) != 0)
    {
      fprintf (stderr, "Could not close %s.\n",outfile_name);
      exit(EXIT_FAILURE);
    }

  if (fclose (in_file) != 0)
    {
      fprintf (stderr, "Could not close %s.\n",infile_name);
      exit(EXIT_FAILURE);
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

  /*puts(the_tag);*/

  if (strcmp(the_tag,str2)==0)
    is_tag=1;

  return is_tag;
}


