#include <math.h>
#include <ncurses.h>
#include <unistd.h>
#include "str.h"

#define pi 3.141592 // it aint that deep
#define twopie pi * 2
#define second 1000000

#define getCenter(vec) { getmaxyx(stdscr, vec.y, vec.x); vec.x /= 2; vec.y /= 2; }

#define scaleFactor .5

#define relativeSecondScale .6
#define relativeMinuteScale .5
#define relativeHourScale .3
#define relativeRadius .7

typedef struct {
  float x;
  float y;
} vector2;

void drawCircle(float radius, char character) {
  const float stepSize = 1.0f / (twopie * radius);
  const unsigned int stepCount = 2 * twopie * radius;

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
  const float stepSize = 1;

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


int main(int argc, char** argv) {
  unsigned timeRemaining = 0;
  argv++;
  if(--argc == 0) {
    printf("Sorry i need a time in seconds to count down from\ndo tuitimer -t (seconds)\nsee --help for more details\n");
    return 1;
  } 
  //we go through de args now :p
  while(argc) {
    bool containsDash = **argv == '-';
    bool doubleDash = (*argv)[1] == '-' && containsDash;
    if(containsDash && strContainsStr(*argv, "h") && !doubleDash || strContainsStr(*argv, "--help")) {
      puts("HELP:");
      puts("tuitimer is a simple, lightweight terminal cli in c.");
      puts("");
      puts("-h, --help                : Show this help message");
      puts("-t                        : set the length (s) of the timer");
      puts("");
      puts("ARGUMENT FORMATTING:");
      puts("example, set timer for 2 seconds:");
      puts("tuitimer -t 2");
      puts("     flag ^ ^ argument");


      return 0;
    } else if(strIsStr(*argv, "-t")) {
      timeRemaining = strToInt(*(++argv));
      argc--;
    }
    argc--;
  }

  if(timeRemaining == 0) {
    printf("Sorry i need a time in seconds to count down from, either you put in 0 or you didn't include the -t argument\nsee --help for more details\n");
  }

  initscr();

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

    int min;
    {
      int x;
      int y;
      getmaxyx(stdscr, y, x);
      min = x < y ? x : y;
    }
    
    drawCircle(min * relativeRadius, '#');
    drawHand(min * relativeHourScale, angleH, 'h');
    drawHand(min * relativeMinuteScale, angleM, 'm');
    drawHand(min * relativeSecondScale, angleS, 's');

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
