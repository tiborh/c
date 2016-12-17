#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 1024
#define MAXLENGTH LINEWIDTH
#define PATTLENGTH MAXLENGTH/4
#define DEBUG 1
#define MAX_LIST_DEPTH 3
#define LENGTH 4
#define WORDLENGTH 24

void usage(char *);
void command_name(char **,char *); /* Extract program name from full command
				      line if path is given too */
int strepl(char *,char *, char *); /* to replace bits of string (in_what,
				      search_what, replace_it_with_what) */

int main(int argc, char **argv)
{
  FILE *in_file;	/* 1. html file */
  char *infile_name = argv[1]; /* the first argument is the name of the input
				  file */
  char clipped[LENGTH+1];
  char cmd_nam_str[LINEWIDTH+1],in_line[LINEWIDTH+1];
  short int empti = 0, list_depth = 0, li_depth = 0, li_flag=0;
  char li_set[5][WORDLENGTH] = {"admonition","grid","list","note","p"};
  char list_set[2][WORDLENGTH] = {"bridge","list-item"};

  clipped[LENGTH]='\0';

  if(argc == 1)
    {
      command_name(argv,cmd_nam_str);
      usage(cmd_nam_str);
      exit(1);
    }

  if ((in_file = fopen(infile_name, "r")) == (FILE *)NULL)
    {
      fprintf(stderr, "Cannot open \"%s\" for reading. Does the file exist?\n",infile_name);
      exit(EXIT_FAILURE);
    }


  /* go through the file line by line*/
  while(fgets(in_line,sizeof(in_line)-1,in_file) != NULL)
    {
      empti = 1;

      /* 1. Check if in <list>; counter is used, because embedded lists are
	 also possible
	 2. li_depth is a counter for embeddedness depth
	 3. li_flag is a flag which shows if previous tag was a list item or a list*/
      if(strstr(in_line,"<list>") != NULL)
	{
	  list_depth++;
	  li_flag = 0;
	}
      if((li_flag == 1) && (strstr(in_line,"<list-item>") != NULL))
	{
	  li_flag = 0;
	  li_depth--;
	  printf("</list-item>\n");
	}
      if((list_depth > 0) && (strstr(in_line,"<list-item>") != NULL))
	{
	  li_depth++;
	  li_flag=1;
	}
      if((list_depth == 0) && (strstr(in_line,"<list-item>") != NULL))
	strepl(in_line,"<list-item>","<!-- <list-item> -->");
      if((list_depth == 0) && (strstr(in_line,"</list-item>") != NULL))
	strepl(in_line,"</list-item>","<!-- </list-item> -->");
      if((li_depth > 0) && (strstr(in_line,"</list-item>") != NULL))
	{
	  li_flag = 0;
	  li_depth--;
	}
      if((list_depth == 0) && (strstr(in_line,"</list>") != NULL))
	strepl(in_line,"</list>","<!-- </list> -->");
      if((list_depth > 0) && (strstr(in_line,"</list>") != NULL))
	{
	  if ((list_depth > 1) && (li_depth > 0))
	    li_flag = 1;
	  list_depth--;
	}
      printf("%s\n",in_line);


#if DEBUG == 1
      printf("List depth: %d\n",list_depth);
      printf("List item depth: %d\n",li_depth);
      printf("List item flag: %d\n",li_flag);
#endif

      if (strchr(in_line,EOF) != NULL)
	printf("End of file reached.\n");
    }

  if (fclose (in_file) != 0)
    {
      fprintf (stderr, "Could not close %s.\n",infile_name);
      exit(EXIT_FAILURE);
    }

  if (empti == 0)
    printf("File is empty.\n");

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


/* Limitation: looks for only the first occurrence of the pattern */
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
   copy the assembled text into the original array, replacing the original
   string */
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
