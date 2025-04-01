#include "math.h"
#include <ncurses.h>

typedef struct {
  float x;
  float y;
} vector2;

void drawCircle(float radius, char character) {
  // there's a *real* way to do this and it's kinda evil but :)
  // what you do is you store the first quarter of the rotations
  // from 0 r to pi / 2 r
  // but oh ho ho how do we decide how our accuraccy
  const unsigned int stepCount = 20;
  const float stepSize = M_PI / (2 * stepCount);

  vector2 stepArr[stepCount];
  for(int i = 0; i < stepCount; i++) {
    stepArr[i] = (vector2){cos(i * stepSize), sin(i * stepSize)};
  }
}

int main() {
  initscr();

  mvprintw(0, 0, "Hello world!");
  getch();

  endwin();
  return 0;
}
