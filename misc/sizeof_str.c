#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
  printf("sizeof \"pink\": %d\n",sizeof "pink");
  printf("sizeof \"purple\": %d\n",sizeof "purple");
  printf("length of \"pink\": %d\n",strlen("pink"));
  printf("length of \"purple\": %d\n",strlen("purple"));


  char* colours[] = {"pink","purple","black","white","green","青","黄色"};
  int array_size = sizeof colours;
  printf("sizeof 'colours': %d\n",array_size);
  int array_length = sizeof(colours)/sizeof(colours[0]);
  printf("sizeof(colours)/sizeof(colours[0]: %d\n",array_length);
  for (int i = 0; i < array_length; i++)
    printf("colours[%d]: %7s\t(%d) (%d)\n",i,colours[i],sizeof(colours[i]),strlen(colours[i]));

  return 0;
}
