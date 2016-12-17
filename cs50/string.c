#include <stdio.h>
#include <string.h>		/* needed for strings */

int main(int argc, char **argv) {
  char inventory[80];		/* "string" as a type of the example does not work */

  strcpy(inventory,"Orange");	/* no direct assignment */

  printf("%s\n",inventory);

  return 0;
}
