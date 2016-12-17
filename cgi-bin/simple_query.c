#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  char *data;
  long m,n;
  printf("%s%c%c\n",
	 "Content-Type:text/html;charset=utf-8",13,10);

  printf("<!doctype html>\n");
  printf("<html>\n");

  printf("<head>\n");
  printf("<title>Multiplication results</title>\n");
  printf("</head>\n");

  printf("<body>\n");

  printf("<h3>Multiplication results</h3>\n");
  data = getenv("QUERY_STRING");
  if(data == NULL)
    printf("<p>Error! Error in passing data from form to script.</p>\n");
  else if(sscanf(data,"m=%ld&n=%ld",&m,&n)!=2)
    printf("<p>Error! Invalid data. Data must be numeric.</p>\n");
  else
    printf("<p>The product of %ld and %ld is %ld.</p>\n",m,n,m*n);

  printf("</body>\n");
  printf("</html>\n");

  return 0;
}
