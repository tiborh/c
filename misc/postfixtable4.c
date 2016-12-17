#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 1024
#define MAXLENGTH LINEWIDTH
#define PATTLENGTH MAXLENGTH/4
#define DEBUG 0
#define MAX_LIST_DEPTH 3
#define LENGTH 4
#define WORDLENGTH 24

void usage(char *);
void command_name(char **,char *); /* Extract program name from full command
				      line if path is given too */
int get_substr(char *, char *);	   /* used to find tags in a line */
int strepl(char *,char *, char *); /* to replace bits of string (in_what,
				      search_what, replace_it_with_what) */
int get_strfromtag(char *, char *, char *); /* to get the string attribute text (orig, tag2find, extracted) */
int filltmp(char *, char *, char *);	    /* extracts a string between two pointers */
int str_prepend(char *, char *);	    /* inserts the second string to the front of the first string */
int tag_del(char *, char *);		    /* dels the second string in the first one, if present */

int main(int argc, char **argv)
{
  FILE *in_file;	/* 1. html file */
  char *infile_name = argv[1]; /* the first argument is the name of the input
				  file */
  int hold_flag=0,list_hold=0,sl_hold=0,slhold_flag=0,list_change_flag=0;
  char cmd_nam_str[LINEWIDTH+1],in_line[LINEWIDTH+1],old_line[LINEWIDTH+1],hold_line[LINEWIDTH+1],str_extract[LINEWIDTH/4],str_assembled[LINEWIDTH/4];


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

  in_line[0]='\0';
  old_line[0]='\0';
  hold_line[0]='\0';

  /* go through the file line by line*/
  while(fgets(in_line,sizeof(in_line)-1,in_file) != NULL)
    {
      /* remove commented out items that would disturb later operations */
      if(strstr(in_line,"<!--<list>-->") != NULL)
	strepl(in_line,"<!--<list>-->","");
      if(strstr(in_line,"<!--</list>-->") != NULL)
	strepl(in_line,"<!--</list>-->","");
	
     /* to place embedded <list> environment into the <sl-item>
	target structure: <sl-item><p>...</p><list>...</list></sl-item>
      */
      if((strstr(old_line,"</p></sl-item>") != NULL) && (strstr(in_line,"<list>") != NULL))
	{
	  strepl(old_line,"</p></sl-item>","</p>");
	  strcpy(hold_line,"</sl-item>");
	  slhold_flag=1;
	  sl_hold=1;
	}
      /*
      if((strstr(in_line,"<list>") != NULL) && (slhold_flag == 1))
	{
	  slhold_flag=0;
	  printf("***slhold_flag reset\n");
	}
      */
      if((strstr(in_line,"</list>") != NULL) && (slhold_flag == 1))
	{
	  if(sl_hold==0)
	    sl_hold=1;
	  else
	    {
	      printf("%s",old_line);
	      strcat(in_line,hold_line);
	      slhold_flag=0;
	      hold_line[0]='\0';
	      sl_hold=0;
	    }
	}
      /* if a <list> is declared immediately after an <step-list> tag,
	 it is commented out and <list-item> tags are changed accordingly.
       */
      if((strstr(old_line,"<step-list>") != NULL) && (strstr(in_line,"<list>") != NULL))
	{
	  strepl(in_line,"<list>","<!--<list>-->");
	  list_change_flag = 1;
	}
      if((list_change_flag == 1) && (strstr(in_line,"<list-item>") != NULL))
	strepl(in_line,"<list-item>","<sl-item>");
      if((list_change_flag == 1) && (strstr(in_line,"</list-item>") != NULL))
	strepl(in_line,"</list-item>","</sl-item>");
      if((list_change_flag == 1) && (strstr(in_line,"</list>") != NULL))
	{
	  strepl(in_line,"</list>","<!--</list>-->");
	  list_change_flag = 0;
	}
      printf("%s",old_line);
      strcpy(old_line,in_line);
    }
    puts(old_line);

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

/* extract tagname; 
   limitations: 
   1. only the first of a kind is found on every line,
   2. closing '>' is not checked for.*/
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

/* to insert "str_which" before "str_into" */
int str_prepend(char *str_into, char *str_which)
{
  char strtmp[LINEWIDTH];

  strtmp[0]='\0';
  strcpy(strtmp,str_into);
  strcpy(str_into,str_which);
  strcat(str_into,strtmp);

  return 0;
}

/* Search and destroy tag2del in str_orig */
int tag_del(char *str_orig, char *tag2del)
{
  char  *str_start, *str_end;
  char str_searched[LINEWIDTH+1];
  char strtmp[LINEWIDTH+1];

  strtmp[0]='\0';
  str_searched[0]='<';
  str_searched[1]='\0';
  strcat(str_searched,tag2del);

  /* 1. Is searched string in the original string? */
  if((str_start = strstr(str_orig,str_searched)) == NULL)
    return -1;
  if ((str_end = strchr(str_start,'>')) == NULL)
    return 1;

  /* 2. get the tag from < to >...*/
  filltmp(strtmp,str_start,str_end);

  /* ... and store it in an char array */
  strcpy(str_searched,strtmp);

#if DEBUG == 1
  printf("str_start: %c\n",*str_start);
  printf("str_end: %c\n",*str_end);
  printf("assembled tag: |%s|\n",str_searched);
#endif

  strepl(str_orig,str_searched,"");

    return 0;
}
