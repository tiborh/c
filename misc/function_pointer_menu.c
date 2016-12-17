#include <stdio.h>
#include "menu_items.h"

/* included in menu_items.h */
extern void item1(void);
extern void item2(void);
extern void item3(void);
extern int show_menu(void);

int main(int argc, char** argv)
{
  void(*farray[])(void) = {item1,item2,item3};
  int loopcounter = 0;
  while(1)
    {
      int choice = show_menu();
#ifdef DEBUG
      if (++loopcounter == 100)
	{
	  printf("probably a runaway loop in %s at line %d",__FILE__,__LINE__);
	  break;
	}
      printf("choice: %d (%s:%d)\n",choice,__FILE__,__LINE__);
#endif
      if (choice >= 1 && choice <= 3)
	farray[choice-1]();
      else
	break;
    }

  return 0;
}
