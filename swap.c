#include <stdio.h>
#include <malloc.h>

#define LINE 80

void swap_ints(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void print_numbers(char *msg,int* to_print)
{
  printf("%s: %d %d\n",msg,*to_print,*(to_print+1));
}

int* get_input(char *ask,int num)
{
  puts(ask);
  char input_line[LINE + 1];
  fgets(input_line,LINE,stdin);
  int* output = malloc(num * sizeof(int));
  sscanf(input_line,"%d %d\n",output,output+1);
  print_numbers("read in",output);

  return output;
}

int main(int argc, char** argv)
{
  int* numbers = get_input("Give me two numbers",2);
  print_numbers("returned",numbers);
  swap_ints(numbers,numbers+1);
  print_numbers("after_swap",numbers);
  free(numbers);
  return 0;
}
