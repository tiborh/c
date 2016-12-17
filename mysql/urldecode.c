//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <math.h>
#include <ctype.h>
//#include <stdbool.h>

void msgdecode(char *dst, const char *src)
{
  char a, b;
  while (*src) {
    if (*src == '+')
      {
	*dst = ' ';
	++src;
	++dst;
      }
    else if ((*src == '%') &&
	((a = src[1]) && (b = src[2])) &&
	(isxdigit(a) && isxdigit(b))) {
      if (a >= 'a')
	a -= 'a'-'A';
      if (a >= 'A')
	a -= ('A' - 10);
      else
	a -= '0';
      if (b >= 'a')
	b -= 'a'-'A';
      if (b >= 'A')
	b -= ('A' - 10);
      else
	b -= '0';
      *dst++ = 16*a+b;
      src+=3;
    } else {
      *dst++ = *src++;
    }
  }
  *dst++ = '\0';
}

int main(int argc, char** argv)
{
  char* dst = malloc(sizeof(char) * 8192);
  char* src = "select eriref%2Cstatus%2Cdatediff%28+curdate%28%29%2C+str_to_date%28regdate%2C+%27%25Y-%25m-%25d%27%29%29+as+%27regdays%27%0D%0Afrom+TR+%0D%0Awhere+datediff%28+curdate%28%29%2C+str_to_date%28regdate%2C+%27%25Y-%25m-%25d%27%29+%29+%3C%3D+3%0D%0Aorder+by+datediff%28+curdate%28%29%2C+str_to_date%28regdate%2C+%27%25Y-%25m-%25d%27%29+%29";

  msgdecode(dst,src);
  printf("Before decoding:\n'%s'\n",src);
  printf("After decoding:\n'%s'\n",dst);

  return 0;
}
