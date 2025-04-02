#include <math.h>
#include <ncurses.h>
#include <unistd.h>

#define pi 3.141592 // it aint that deep
#define second 1000000

#define getCenter(vec) { getmaxyx(stdscr, vec.y, vec.x); vec.x /= 2; vec.y /= 2; }

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
  const unsigned int stepCount = radius;
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

void toTime(unsigned timeLeft, float* seconds, float* minutes, float* hours) {
  // this aint too hard :p
  *seconds = timeLeft % 60;
  *minutes = timeLeft / 60.0f;
  *hours = timeLeft / 3600.0f;
}

int main() {
  initscr();

  unsigned timeRemaining = 60 * 2; // we'll worry abt setting this later

  curs_set(0);
  nodelay(stdscr, true);

  while(timeRemaining-- > 0) {
    float timeS;
    float timeM;
    float timeH;
    toTime(timeRemaining, &timeS, &timeM, &timeH);

    float angleS = pi * 2 * (timeS / 60.0f) - pi / 2;
    float angleM = pi * 2 * (timeM / 60.0f) - pi / 2;
    float angleH = pi * 2 * (timeH / 24.0f) - pi / 2;

    erase();
    
    drawCircle(30, '#');
    drawHand(30, angleM, 'm');
    drawHand(30, angleS, 's');
    drawHand(30, angleH, 'h');

    refresh();

    for(int i = 0; i < 10; i++) {
      usleep(second / 10);
      if(getch() != 'q')
        continue;
      timeRemaining = 0;
      break;
    }
  }

  endwin();
  return 0;
}
