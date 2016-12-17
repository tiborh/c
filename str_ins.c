#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

int str_ins(char *, char *, int);
int str_copy(char *, char *);

int main(int argc, char *argv[])
{
  char str1_test[256]="standardised", str2_test[256]="empty", ptr_start;

    if (argc < 3)
    {
      printf("Usage: %s input_file output_file\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  else
    {
      puts(str1_test);
      str_copy(str1_test+2,str2_test);
      puts(str2_test);
    }



  exit(EXIT_SUCCESS);
}

int str_ins(char *str_orig, char *str_in, int ins_point)
{
  int i;
  char str_buff[LINEWIDTH];
  
  

  return(1);
}

int str_copy(char *str_from, char *str_into)
{
  int i=0;
  
  do{
    *(str_into+i) = *(str_from+i);
  }while(*(str_from+i++)!='\0');

  return(1);
}
