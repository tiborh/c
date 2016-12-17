#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

int main(int argc, char *argv[])
{
  FILE *in_file, *out_file;
  char *infile_name = "file.lst", *outfile_name = "out.lst";
  char in_line[LINEWIDTH+1], *temp_char;

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
}











