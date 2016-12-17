#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void print_flags(int *);	   /* used for diagnostic purposes */
void zero_flags(int *,int);	   /* reset flags below given level */
int strepl(char *,char *, char *); /* to replace bits of string (in_what, search_what, replace_it_with_what) */

int main(int argc, char *argv[])
{
  FILE *in_file, *out_file, *list_file;	/* 1. html file 2. tmp file for table creation */
  char *infile_name = argv[1]; 	/* the first argument is the name of the input file */
  char cmd_nam_str[LINEWIDTH+1],in_line[LINEWIDTH+1],caption_text[LINEWIDTH]="";
  short int i,j,k;
  char head_in_line[LINEWIDTH]="<chl1>"; /* heading tag */
  int flags[MAX_HEAD_DEPTH+1]={0};  
  short int table_flag=0,limbo_flag=0,list_limbo=0,write_list_limbo=0,row_flag=0,caption_flag=0,steplist_flag=0,slitem_flag=0,title_flag=0,li_flag=0,entry_flag=0,tp_flag=0;
  short int p_flag=0; /* p_flag is used only to get a </p> tag where <p> needed to be inserted earlier! */
  short int row_counter=0,cell_counter=0,list_depth=0,li_depth=0;
  size_t length = LENGTH;
  char searched = 'c';
  char clipped[LENGTH+1];

  clipped[LENGTH]='\0';

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
     based on the table cell count of the first table row */
  while(fgets(in_line,sizeof(in_line)-1,in_file) != NULL)
    {

      /* Check if list items are inside (step-)list environment */
      if (get_substr(in_line,"step-list") == 0)
	{
	  if (steplist_flag==0) 
	    steplist_flag=1;
	  else
	    strepl(in_line,"<step-list>","<!--<step-list>-->");
	}
      if ((strstr(in_line,"<sl-item>") != NULL) && (steplist_flag == 1))
	slitem_flag = 1;
      if ((strstr(in_line,"</sl-item>") != NULL) && (steplist_flag == 1))
	slitem_flag = 0;
      if ((strstr(in_line,"<list>") != NULL) && (steplist_flag == 1) && (slitem_flag ==0))
	strepl(in_line,"<list>","<sl-item>\n<list>");
      if ((strstr(in_line,"</list>") != NULL) && (steplist_flag == 1) && (slitem_flag ==0))
	strepl(in_line,"</list>","</list>\n</sl-item>");
      if ((strstr(in_line,"<sl-item>") != NULL) && (steplist_flag == 0))
	strepl(in_line,"<sl-item>","<!--<sl-item>-->");
      if ((strstr(in_line,"</sl-item>") != NULL) && (steplist_flag == 0))
	strepl(in_line,"</sl-item>","<!--</sl-item>-->");
      if (get_substr(in_line,"/step-list") == 0)
	{
	  if (steplist_flag == 1)
	    steplist_flag=0;
	  else
	    strepl(in_line,"</step-list>","<!--</step-list>-->");
	}

      /* 1. Check if in <list>; counter is used, because embedded lists are
	 also possible
	 2. li_depth is a counter for <list-item> embeddedness level
	 3. li_flag is a flag which shows if previous tag was a list item
	 a list tag resets it to zero when it starts and sets it back to one 
	 when it finishes
	 4. an embedded <list> environment can only be inside a <list-item> 
	 environment, therefore, it needs to be temped out into a file until 
	 it can be placed into one.
	 5. inside a <list-item> environment, text needs to be included in 
	 a <p> environment*/
      if(strstr(in_line,"<list>") != NULL)
	{
	  if((list_depth > 0) && (li_flag == 0))
	    {
	      if ((list_file = tmpfile()) == (FILE *)NULL)
		{
		  fprintf(stderr, "Cannot open temporary file.\n");
		  exit(EXIT_FAILURE);
		}
	      list_limbo=1;
	      write_list_limbo=0;
	    }
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
	  if(strstr(in_line,"<p>")==NULL)
	    {
	      strcat(in_line,"<p>");
	      p_flag=1;
	    }
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
	  if (p_flag == 1)
	    {
	      printf("</p>\n");
	      p_flag = 0;
	    }
	  if (write_list_limbo == 1)
	    {
	      print_file(list_file);
	      fclose(list_file);
	    }
	}
      if((list_depth == 0) && (strstr(in_line,"</list>") != NULL))
	strepl(in_line,"</list>","<!-- </list> -->");
      if((list_depth > 0) && (strstr(in_line,"</list>") != NULL))
	{
	  if ((list_depth > 1) && (li_depth > 0))
	    li_flag = 1;
	  list_depth--;
	  if (list_limbo == 1)
	    {
	      fprintf(list_file,"%s",in_line);
	      list_limbo = 0;
	      write_list_limbo = 1;
	      continue;
	    }
	}

      if (get_substr(in_line,"title") == 0)
	title_flag=1;
      if ((strstr(in_line,"</title>") != NULL) && (title_flag == 0))
	strepl(in_line,"</title>","<!--</title>-->");
      if (get_substr(in_line,"/title") == 0)
	title_flag=0;


      /* head/<chlx>/ close tags */
      /* what does it do? 
	 0. head_in_line has the current head level, [4] storing the number 
	 1. srncopy copies the tag without <> into clipped
	 2. checked if clipped tag is in in_line 
	 3. open lower level headings are closed 
	 4. flag to new heading level is set to 1*/
      for (i=1,j=MAX_HEAD_DEPTH;i<=MAX_HEAD_DEPTH;i++,j--)
	{
	  head_in_line[4]=i+48;
	  strncpy(clipped,strchr(head_in_line,searched),length);
	  
	  if (get_substr(in_line,clipped) == 0)
	    {
	      zero_flags(flags,i);
	      flags[i]=1;
#if DEBUG == 1
	      printf("%s",head_in_line);
	      printf("clipped: %s\n",clipped);
	      print_flags(flags);
#endif
	    }
	}
      k++;

      /*beginning of the table section*/
      /* 1. the table cannot be inside a (step-)list environment. */
      /* 2. number of columns need to be specified, therefore cells are counted,
	 for which temporary buffer file is created, as the number of columns appear
	 before the cells can be counted.*/
      /* 3. <tgroup> environment, and <colspec> tags have to be provided */
      /* 4. <caption> environment is also necessary */
      /* Note: until the end of the first line (in limbo), lines are written into a 
	 temporary file (out_file)*/
      /* 5. <entry> and <tp> environments need to be closed by </tp> and </entry> tags */
      if (get_substr(in_line,"table") == 0)
	{
	  if ((out_file = tmpfile()) == (FILE *)NULL)
	    {
	      fprintf(stderr, "Cannot open temporary file.\n");
	      exit(EXIT_FAILURE);
	    }
	  table_flag=1;
	  if (steplist_flag == 1)
	    printf("</step-list>\n");
#if DEBUG == 1
	  printf("<<<in table\n");
#endif
#if DEBUG == 2
	  printf("***%s***",in_line);
#endif
	}
      if (get_substr(in_line,"tgroup") == 0)
	{
	  limbo_flag=1;
#if DEBUG == 1
	  printf("<<<in limbo\n");
#endif
	  continue;
	}

      if (get_substr(in_line,"caption") == 0)
	{
	  caption_flag = 1;
#if DEBUG == 1
	  printf("<<<in caption\n");
#endif
	  continue;
	}
      if (caption_flag == 1)
	{
	  /*strcpy(caption_text,in_line);*/
	  caption_flag = 0;
	}
      if (get_substr(in_line,"/caption") == 0)
 	{ 
	  caption_flag = 0;
#if DEBUG == 1
	  printf("<<<out of caption\n");
#endif
	  continue;
	}
      /*
      if (get_substr(in_line,"caption") == 0)
	continue;
      */
	  
      if ((get_substr(in_line,"row") == 0) && (table_flag == 1))
	{
	  row_flag=1;
	  row_counter++;
#if DEBUG == 1
	  printf("<<<in row\n");
	  printf("***row_counter: %d\n",row_counter);
#endif
	}

      if (get_substr(in_line,"/row") == 0)
	{
	  row_flag=0;
	  if(tp_flag == 1)
	    {
	      tp_flag=0;
	      strepl(in_line,"</row>","</tp>\n</row>");
	    }
	  if(entry_flag == 1)
	    {
	      entry_flag=0;
	      strepl(in_line,"</row>","</entry>\n</row>");
	    }
	}

      if (strlen(in_line) > 1)
	{
	  if ((limbo_flag == 1) || (row_counter == 1) || (list_limbo == 1))
	    {	    
	      if ((limbo_flag == 1) || (row_counter == 1))
		fprintf(out_file,"%s",in_line);
	      if (list_limbo == 1)
		fprintf(list_file,"%s",in_line);
	    }
	  else
	    printf("%s",in_line);
	}
      if ((row_flag ==1) && (get_substr(in_line,"entry") == 0))
	++cell_counter;
      if (get_substr(in_line,"/row") == 0)
	{
#if DEBUG == 1
	  printf("tp_flag: %d, entry_flag: %d\n",tp_flag,entry_flag);
	  printf("in_line after strepl: {{{{%s}}}}\n",in_line);
	  printf("<<<out of row\n");
#endif
	  if (row_counter == 1)
	    {
	      printf("<caption>%s</caption>\n",caption_text);
	      strcpy(caption_text,"");
	      printf("<tgroup cols=\"%d\">",cell_counter);
	      for(i=0;i<cell_counter;i++)
		printf("<colspec colname=\"col%d\"/>",i+1);
	      printf("\n");
	      print_file(out_file);
	    }
	  limbo_flag=0;
#if DEBUG == 1
	  printf("<<<out of limbo\n");
#endif
	  cell_counter=0;
	}
      if (get_substr(in_line,"/table") == 0)
	{
	  table_flag=0;
	  row_counter=0;
	  if (steplist_flag == 1)
	    printf("<step-list reset=\"no\">\n");	  
#if DEBUG == 1
	  printf("<<<out of table\n");
#endif
	  if (fclose (out_file) != 0)
	    {
	      fprintf (stderr, "Could not close temporary file.\n");
	      exit(EXIT_FAILURE);
	    }
	}
      if(get_substr(in_line,"entry") == 0)
	{
	  if (row_flag == 1)
	    entry_flag = 1;
	  else
	    strepl(in_line,"<entry>","<!--<entry>-->");
	}
      if(get_substr(in_line,"tp") == 0)
	{
	  if (entry_flag == 1)
	    {
	      if (row_flag == 1)
		tp_flag = 1;
	      else
		strepl(in_line,"<tp>","<!--<tp>-->");
	    }
	}
      if(get_substr(in_line,"/tp") == 0)
	{	 
	  if (tp_flag == 1)
	    tp_flag = 0;
	  else
	    strepl(in_line,"</tp>","<!--</tp>-->");
	}
      if(get_substr(in_line,"/entry") == 0)
	{	 
	  if (entry_flag == 1)
	    entry_flag = 0;
	  else
	    strepl(in_line,"</entry>","<!--</entry>-->");
	}
	  
    }

  i=1;
  flags[1]=1;
  zero_flags(flags,i);
  printf("</body>\n");
  printf("</doc>\n");

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


/* print file line by line */
void print_file(FILE *file_to_print)
{
  char in_line[LINEWIDTH+1];

  rewind(file_to_print);

  while(fgets(in_line,sizeof(in_line)-1,file_to_print) != NULL)
    printf("%s",in_line);

  return;
}

  /* input: heading level tags and current head level */
  /* what does it do?  */
void zero_flags(int *inarray,int i)
{
  char out_line[LINEWIDTH+1]="</chl1>";
  int j;

  for(j=MAX_HEAD_DEPTH;j>=i;j--)
    {
      if (*(inarray+j)==1)
	{
	  out_line[5]=j+48;
#if DEBUG == 1
	  puts(out_line);
#endif
	}
      *(inarray+j)=0;
    }
}

/* for diagnostic purposes */
void print_flags(int *inarray)
{
  int i;
  printf("(");
  for (i=1;i<=MAX_HEAD_DEPTH;i++)
    printf("%d",*(inarray+i));
  printf(")\n");
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
   copy the assembled text into the original array, replacing the original string */
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
