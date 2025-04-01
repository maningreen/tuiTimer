#include <ncurses.h>

int main() {
  initscr();

  mvprintw(0, 0, "Hello world!");
  getch();

  endwin();
  return 0;
}
