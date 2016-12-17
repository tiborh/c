#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void*, const void*);
void print_str_array(char**, int);

int main(int argc, char** argv)
{
  char* colours[] = {"pink","purple","black","white","green","青","黄色","灰色","赤","緑"};
  const unsigned int size_of_first = sizeof(colours[0]);
  const unsigned int array_length = sizeof(colours)/size_of_first;

  puts("Before sort:");
  print_str_array(colours,array_length);

  qsort(colours, array_length, size_of_first, comp);
  
  puts("After sort:");
  print_str_array(colours,array_length);

  return 0;
}

int comp(const void* boo, const void* bah)
{
  char* a = *(char **) boo;
  char* b = *(char **) bah;

  return strcmp(a,b);
}

void print_str_array(char* inarr[], int length)
{
    for(int i = 0; i < length; i++)
      puts(inarr[i]);
}
