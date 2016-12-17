#include <stdio.h>

int main(int argc, char** argv)
{
  const char* chars= "abcdef";
  puts("const char*");
  putchar(*chars);
  putchar('\n');
  putchar(*(chars+1));
  putchar('\n');
  putchar(*++chars);
  putchar('\n');
  puts("this one leads to error:");
  puts("*++chars = 'u';");
  puts("Error text: assignment of read-only location");
  putchar('\n');

  char* const chars2 = "ghijkl";
  puts("char* const");
  putchar(*chars2);
  putchar('\n');
  putchar(*(chars2+1));
  putchar('\n');
  puts("this one leads to error:");
  puts("putchar(*++chars2);");
  puts("Error text: increment of read-only variable");
  puts("this one gives no compilation error, only segfault at execution time:");
  puts("*chars2 = 'u'");
  return 0;
}
