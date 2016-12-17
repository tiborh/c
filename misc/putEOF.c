#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  char ch = -1; 		/* EOF */
  FILE *out_file;
  char *outfile_name = argv[1];

  if ((out_file = fopen(outfile_name, "w")) == (FILE *)NULL)
    {
      fprintf(stderr, "Cannot open \"%s\" for writing.\n",outfile_name);
      exit(EXIT_FAILURE);
    }

  fputc(ch,out_file);

  if (fclose (out_file) != 0)
    {
      fprintf (stderr, "Could not close %s.\n",outfile_name);
      exit(EXIT_FAILURE);
    }

  return 0;
}
