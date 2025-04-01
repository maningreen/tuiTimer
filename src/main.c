#include "math.h"
#include <ncurses.h>

typedef struct {
  float x;
  float y;
} vector2;

#define scaleFactor .5

void drawCircle(float radius, char character) {
  // there's a *real* way to do this and it's kinda evil but :)
  // what you do is you store the first quarter of the rotations
  // from 0 r to pi / 2 r
  // but oh ho ho how do we decide how our accuraccy
  const unsigned int stepCount = 20;
  const float stepSize = M_PI / (2 * stepCount);

  vector2 center; 
  getmaxyx(stdscr, center.y, center.x);
  center.x /= 2;
  center.y /= 2;

  for(int i = 0; i < stepCount; i++) {
    vector2 item = (vector2){radius * cos(i * stepSize), radius * sin(i * stepSize) * scaleFactor};
    mvprintw(center.y + item.y, center.x + item.x, "%c", character);
    mvprintw(center.y + -item.y, center.x + item.x, "%c", character);
    mvprintw(center.y + item.y, center.x + -item.x, "%c", character);
    mvprintw(center.y + -item.y, center.x + -item.x, "%c", character);
  }
}

int main() {
  initscr();

  drawCircle(10, 'H');
  refresh();
  getch();

  endwin();
  return 0;
}
