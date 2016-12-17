#include <stdio.h>

#define LINEWIDTH 1024
#define WORDLENGTH 24

int main(int argc, char **argv)
{
  char li_set[5][WORDLENGTH] = {"admonition","grid","list","note","p"};
  char list_set[2][WORDLENGTH] = {"bridge","list-item"};

  printf("sizeof array 1: %d\n",sizeof(li_set)/WORDLENGTH);
  printf("sizeof array 2: %d\n",sizeof(list_set)/WORDLENGTH);

  return 0;
}
