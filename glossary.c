#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINEWIDTH 1024
#define MAXLENGTH LINEWIDTH
#define PATTLENGTH MAXLENGTH/4
#define DEBUG 0
#define MAX_HEAD_DEPTH 4
#define LENGTH 4

void usage(char *);
void command_name(char **,char *); /* Extract program name from full command line if path is given too */
int get_substr(char *, char *);	   /* used to find tags in a line */
void print_file(FILE *);	   /* used to print lines of the temp file */
int strepl(char *,char *, char *); /* to replace bits of string (in_what, search_what, replace_it_with_what) */
void bprint (char *,int);	   /* to print debug info */
bool isodd(int );

int main(int argc, char *argv[])
{
  FILE *in_file;	/* 1. glossary in table format */
  char *infile_name = argv[1]; 	/* the first argument is the name of the input file */
  char cmd_nam_str[LINEWIDTH+1],in_line[LINEWIDTH+1];
  bool firstcell=true;

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

  /* go through the file line by line and print the table with correct colspec data 
     based on the table cell count of the first table row 
  */
  while(fgets(in_line,sizeof(in_line)-1,in_file) != NULL)
    {
      if(strstr(in_line,"<row>")!=NULL)
	{
	  firstcell=true;
	  strepl(in_line,"<row>","<gl-item>");
	}
      if(strstr(in_line,"</row>")!=NULL)
	  strepl(in_line,"</row>","</gl-item>");
      if(strstr(in_line,"</entry>")!=NULL)
	continue;

      if(strstr(in_line,"<entry")!=NULL)
	{
	  if (strepl(in_line,"<entry><tp>",(firstcell)?"<term>":"<expansion><p>") == 1)
	    strepl(in_line,"<entry valign=\"middle\"><tp>",(firstcell)?"<term>":"<expansion><p>");
	  /*
	  if(firstcell)
	    "<term>");
	  else
	    strepl(in_line,"<entry><tp>","<expansion>");
	  */
	}
      if(strstr(in_line,"</tp>")!=NULL)
	{
	  if(firstcell)
	    {
	      strepl(in_line,"</tp>","</term>");
	      firstcell=false;
	    }
	  else
	    strepl(in_line,"</tp>","</p></expansion>");
	}

      /*
      rowcount++;
      oddbool=isodd(rowcount);
      if(oddbool)
	printf("Odd numbered row\n");
      else
	printf("Even numbered row\n");
      */

      printf("%s",in_line);
    }
  return 0;
}

bool isodd(in_num)
{
  int tempint;
  
  tempint=in_num;

  tempint>>=1;
  tempint<<=1;

  if (in_num == tempint)
    return false;
  else
    return true;
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

/* extract tagname; 
   limitations: 
   1. only the first of a kind is found on every line,
   2. closing '>' is not checked for.
*/
int get_substr(char *str1, char *str2)
{
  char  *str_start;
  char str_searched[LINEWIDTH+1];

  str_searched[0]='<';
  str_searched[1]='\0';
  strcat(str_searched,str2);
  strcat(str_searched,"\0");
  /*  strcat(str_searched,">\0");*/

#if DEBUG == 2
  printf("assembled tag: |%s|\n",str_searched);
#endif

  if((str_start = strstr(str1,str_searched)) == NULL)
    return -1;
  else
    return 0;
}


/* print file line by line */
void print_file(FILE *file_to_print)
{
  char in_line[LINEWIDTH+1];

  rewind(file_to_print);

  while(fgets(in_line,sizeof(in_line)-1,file_to_print) != NULL)
    printf("%s",in_line);

  return;
}

/* Limitation: looks for only the first occurrence of the pattern */
int strepl(char *strin,char *strpat1, char *strpat2)
{
  char strtmp[MAXLENGTH];
  char *ptrstr, *ptrtmp;
  int i=0;

/* phase zero: 
   - pointers set to first char of the input string
   - temporary string is set to null string 
*/
  ptrstr = ptrtmp = strin;
  strtmp[0] = '\0';

  /* if line is empty, stop. */
  if (strin[0] == '\0')
    return 1;

/* phase one:
   check if searched pattern can be found in string 
*/
  if ((ptrstr = strstr(strin,strpat1)) != NULL)
    {
/* phase two:
   check if the pattern is in front position 
*/
      if (strin != ptrstr)
	{
/* phase three:
   if not, copy text before the pattern into temp string 
*/
	  ptrtmp = strin;
	  do
	    strtmp[i++] = *ptrtmp;
	  while(++ptrtmp != ptrstr);
	  strtmp[i] = '\0';
	}
/* phase four: 
   put the replacement pattern into temp string 
*/
      strcat(strtmp,strpat2);
      ptrtmp+=strlen(strpat1);
/* phases five and six:
   - check if there's any text after the pattern
   - if so, concatenate it to the temp string 
*/
      if (*strtmp != '\0')
	strcat(strtmp,ptrtmp);
/* step seven:
   copy the assembled text into the original array, replacing the original string 
*/
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

void bprint (char *str2print, int val2print)
{
#if DEBUG == 1
  printf("%s: %d\n",str2print,val2print);
#endif
}
