#include <stdio.h>
#include "menu_items.h"
#include <stdlib.h>
#include <string.h>

void item1(void)
{
  puts("item1 has been selected");
  getchar();
}

void item2(void)
{
  puts("item2 has been selected");
  getchar();
}

void item3(void)
{
  puts("item3 has been selected");
  getchar();
}

int show_menu(void)
{
  int choice = 0;
  char input[LENGTH+1] = "";
  char msgstr[LENGTH+1] = "";
#ifdef DEBUG
  int loopcounter = 0;
#endif
  do
    {
#ifndef DEBUG
      system("clear");
#endif
      puts("1. menu item 1");
      puts("2. menu item 2");
      puts("3. menu item 3");
      puts("4. exit");
      printf("%s",msgstr);
      msgstr[0] = '\0';
      if (fgets(input,LENGTH,stdin) == NULL)
	{
	  strcat(msgstr,"fgets() returns NULL\n");
	  return 0;
	}
      if (sscanf(input,"%d\n",&choice) == 0)
	strcat(msgstr,"No valid key has been entered.\n");
#ifdef DEBUG
      if (++loopcounter == 100)
	{
	  printf("probably a runaway loop in %s at line %d",__FILE__,__LINE__);
	  break;
	}
      printf("choice: %d (%s:%d)\n",choice,__FILE__,__LINE__);
#endif
    } while (choice < 1 || choice > 4);

  return choice;
}
