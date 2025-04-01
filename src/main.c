#include <math.h>
#include <ncurses.h>
#include <unistd.h>

#define pi 3.141592 // it aint that deep

#define getCenter(vec) { getmaxyx(stdscr, vec.y, vec.x); vec.x /= 2; vec.y /= 2;}

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
  const float stepSize = pi / (2 * stepCount);

  vector2 center; 
  getCenter(center);

  for(int i = 0; i < stepCount; i++) {
    vector2 item = (vector2){radius * cos(i * stepSize), radius * sin(i * stepSize) * scaleFactor};
    mvprintw(center.y + item.y, center.x + item.x, "%c", character);
    mvprintw(center.y + -item.y, center.x + item.x, "%c", character);
    mvprintw(center.y + item.y, center.x + -item.x, "%c", character);
    mvprintw(center.y + -item.y, center.x + -item.x, "%c", character);
  }
}

void drawHand(float length, float angle, char character) {
  const float stepSize = .5;

  vector2 scalar = {cos(angle), sin(angle) * scaleFactor};

  vector2 center;
  getCenter(center);

  while(length >= 0) {
    mvprintw((scalar.y * length) + center.y, (scalar.x * length) + center.x, "%c", character);
    length -= stepSize;
  }
}

void toTime(unsigned timeLeft, unsigned* seconds, unsigned* minutes) {
  // this aint too hard :p
  *seconds = timeLeft % 60;
  *minutes = timeLeft / 60;
}

int main() {
  // initscr();

  unsigned timeRemaining = 61; // we'll worry abt setting this later

  while(--timeRemaining > 0) {
    unsigned timeS;
    unsigned timeM;
    toTime(timeRemaining, &timeS, &timeM);
    printf("%u : %u\n", timeM, timeS);
    sleep(1);
  }

  // endwin();
  return 0;
}
