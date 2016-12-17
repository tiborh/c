#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 1024
#define MAXLENGTH LINEWIDTH
#define TAGLENGTH LINEWIDTH/2
#define PATTLENGTH MAXLENGTH/4
#define DEBUG 0
#define MAX_HEAD_DEPTH 4
#define LENGTH 4

void usage(char *);
void command_name(char **,char *); /* Extract program name from full command line if path is given too */
char *get_substr(char *, char *);	   /* used to find tags in a line */
int str_ins(char *, char *, size_t);
void bprint (char *,int);	   /* to print debug info */
int str_prepend(char *, char *);

int main(int argc, char *argv[])
{
  FILE *in_file; 
#if DEBUG == 4
  FILE *debug_file; 
  char *outfile_name="debug_info.txt"
#endif
  char *infile_name = argv[1]; 	/* the first argument is the name of the input file */
  char cmd_nam_str[LINEWIDTH+1],in_line[LINEWIDTH+1];
  short int emph_counter=0;
  char tag_txt[TAGLENGTH];
  char *ptr_tmp;
  int line_num=0;
  
  if(argc == 1)
    { 
      command_name(argv,cmd_nam_str);
      usage(cmd_nam_str);
      exit(1);
    }

  if ((in_file = fopen(infile_name, "r")) == (FILE *)NULL)
    {
      fprintf(stderr, "Cannot open %s.\n",infile_name);
      exit(EXIT_FAILURE);
    }

#if DEBUG > 0
  if ((debug_file = fopen(outfile_name, "w")) == (FILE *)NULL)
    {
      fprintf(stderr, "Cannot open %s.\n",outfile_name);
      exit(EXIT_FAILURE);
    }
#endif

  while(fgets(in_line,sizeof(in_line)-1,in_file) != NULL)
    {
      ptr_tmp = in_line;

      while((ptr_tmp=get_substr(ptr_tmp,tag_txt)) != NULL)
	{
	  ++line_num;
	  if ((strstr(tag_txt,"</emph>")==NULL) && (emph_counter > 0))
	    {
#if DEBUG == 4
	      printf("ptr_tmp: '%d' ",*ptr_tmp);
#endif
	      str_prepend(ptr_tmp-strlen(tag_txt),"</emph>");
	      emph_counter--;
	      ptr_tmp+=strlen("</emph>");
#if DEBUG == 4
	      printf("'%d'\n",*ptr_tmp);
#endif
	    }
	  if (strstr(tag_txt,"emph")!=NULL)
	    {
	      if (strstr(tag_txt,"</emph")!=NULL)
		emph_counter--;
	      else
		emph_counter++;
	      bprint("emph_counter",emph_counter);
	    }
	  /*printf("%s",tag_txt);*/
	}
      /*putchar('\n');*/
#if DEBUG == 4
      if (emph_counter >= 0)
	fprintf(debug_file,"%6d: %3d: %s",line_num,emph_counter,in_line);
#endif

#if DEBUG == 2
      bprint("emph_counter",emph_counter);
#endif
      printf("%s",in_line);
    }

#if DEBUG == 4
  if (fclose (debug_file) != 0)
    {
      fprintf (stderr, "Could not close %s.\n",outfile_name);
      exit(EXIT_FAILURE);
    }
#endif

  if (fclose (in_file) != 0)
    {
      fprintf (stderr, "Could not close %s.\n",infile_name);
      exit(EXIT_FAILURE);
    }

  return 0;
}

/* extract program name */
void command_name(char **argv,char *prg_name)
{
  int j=strlen(argv[0])-1,k=0,i=0;
  char prg_name_tmp[LINEWIDTH];

  while((j >= 0) && (argv[0][j] != '/'))
      prg_name_tmp[k++]=argv[0][j--];

  prg_name_tmp[k--]='\0';

  for(i=0; k>=0; k--, i++)
    prg_name[i]=prg_name_tmp[k];
  prg_name[i]='\0';

  printf("\n");
}

/* print out usage */
void usage(char *prg_nam)
{
  printf("usage: %s file_name\n",prg_nam);
}

void bprint (char *str2print, int val2print)
{
#if DEBUG == 1
  printf("%s: %d\n",str2print,val2print);
#endif
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
  /*  str_start++;
  str_end--;
  */
  /* 3. Copy tag text into str_tag */
  /* removed from condition:   && (*(str_start+i) != ' ') */
  while(str_start+i<=str_end){
    str_tag[i] = *(str_start+i);
    i++;
  }
  str_tag[i]='\0';
  
  /* 4. copy tag text into main()'s array */
  strcpy(str2,str_tag);

#if DEBUG > 0
  printf("|%s|\n",str_tag);
  printf("End char: %c\n",*str_end);
#endif

  return str_end+1;
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

int str_prepend(char *str_into, char *str_which)
{
  char strtmp[LINEWIDTH];

  strtmp[0]='\0';
  strcpy(strtmp,str_into);
  strcpy(str_into,str_which);
  strcat(str_into,strtmp);

  return 0;
}
