#include <stdio.h>

void crashit(void);

int main(int argc, char **argv) {
  crashit();
}

void crashit(void) {
  //printf("made it.\t");
  crashit();
}
