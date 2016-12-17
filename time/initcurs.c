#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {
  clock_t start,end;

  printf("ncurses is initiating...\n");
  start=clock();

  if((initscr())==NULL) {
    perror("initscr");
    exit(EXIT_FAILURE);
  }

  printw("This is an ncurses window.\n");
  refresh();
  sleep(3);

  printw("Going, bye for now.\n");
  refresh();
  sleep(3);
  endwin();
  end = clock();
  printf("The curses window has closed.\n");
  printf("ncurses running time: %.2f seconds\n",(double)(end-start)/(double)(CLOCKS_PER_SEC));

  exit(0);
}
