#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

void usage(char *);
void command_name(char **,char *);

int main(int argc, char **argv)
{
  int i;
  char cmd_nam_str[LINEWIDTH+1];

  printf("argc: %d\n",argc);

  if(argc == 1)
    { 
      command_name(argv,cmd_nam_str);
      usage(cmd_nam_str);
      exit(1);
    }
  for(i=0;i<argc;i++)
    printf("argv[%d]: %s\t(length: %d)\n",i,argv[i],strlen(argv[i]));

  return 0;
}

void command_name(char **argv,char *prg_name)
{
  int j=strlen(argv[0])-1,k=0,i=0;
  char prg_name_tmp[LINEWIDTH];

/*   printf("j: %d\n",j); */

  while((j >= 0) && (argv[0][j] != '/'))
    prg_name_tmp[k++]=argv[0][j--];
/*       printf("%c(k=%d)",argv[0][j+1],k-1); */

  prg_name_tmp[k--]='\0';

  for(i=0; k>=0; k--, i++)
    prg_name[i]=prg_name_tmp[k];
  prg_name[i+1]='\0';

  printf("\n");
}

void usage(char *prg_nam)
{
  printf("usage: %s arg1[arg2 ... argx]\n",prg_nam);
}
