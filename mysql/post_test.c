#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 8196
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN+EXTRA+2
/* 1 for added line break, 1 for trailing NUL */
//#define DATAFILE "../data/data.txt"


void unencode(char *src, char *last, char *dest)
{
  for(; src != last; src++, dest++)
    if(*src == '+')
      *dest = ' ';
    else if(*src == '%') {
      int code;
      if(sscanf(src+1, "%2x", &code) != 1) code = '?';
      *dest = code;
      src +=2; }     
    else
      *dest = *src;
  *dest = '\n';
  *++dest = '\0';
}

int main(void)
{
  char *lenstr;
  char input[MAXINPUT], data[MAXINPUT];
  long len;
  printf("%s%c%c\n",
	 "Content-Type:text/html;charset=iso-8859-1",13,10);
  printf("<title>Response</title>\n");
  lenstr = getenv("CONTENT_LENGTH");
  if(lenstr == NULL || sscanf(lenstr,"%ld",&len)!=1 || len > MAXLEN)
    printf("<p>Error in invocation - wrong FORM probably.</p>");
  else {
    //FILE *f;
    if (!fgets(input, len+1, stdin))
      return 1;
    unencode(input+EXTRA, input+len, data);
    //f = fopen(DATAFILE, "a");
    //if(f == NULL)
    //  printf("<p>Sorry, cannot store your data.</p>");
    //else
    //  fputs(data, f);
    //fclose(f);
    printf("<p>Thank you! The following contribution of yours has been stored:<br>%s</p>",data);
    printf("<p>Raw data:<br />%s</p>\n",input);
  }
  printf("\n");
  return 0;
}
