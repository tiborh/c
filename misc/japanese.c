#include <stdio.h>

int main(int argc, char** argv)
{
  char goodmorning[] = "お早うごさいます。";
  char goodday[] = "今日は。";
  char goodeve[] = "今晩は。";
  char goodnight[] = "お休みなさい。";
  char *greetings[] = {goodmorning,goodday,goodeve,goodnight};

  printf("size of array: \t%u\n",sizeof(greetings));
  printf("size of first element: %u\n",sizeof(greetings[0]));
  for (int i = 0; i < sizeof(greetings)/sizeof(greetings[0]); i++)
    printf("%s\n",greetings[i]);
}
