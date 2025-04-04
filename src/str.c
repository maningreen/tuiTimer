#include <stdbool.h>
#include "str.h"

bool strContainsChar(char* s, char c) {
  while(*s != '\0')
    if(*(s++) == c)
      return true;
  return false;
}

bool strContainsStr(char* first, char* second) {
  while(*first != '\0')
    if(*first == *second) {
      int i = 0;
      for(; *(first++) == *(second++); i++)
        if(*second == '\0')
          return true;
        else if(*first == '\0')
          return false;
      first -= i + 1;
      second -= i;
    } else first++;
  return false;
}

int strToInt(char* s) {
  int val = 0;
  while(*s != '\0')
    val = (val * 10) + *(s++) - '0';
  return val;
}

bool strIsStr(char* first, char* second) {
  while(*(second++) == *(first++))
    if(*first == '\0' && *second == '\0')
      return true;
  return false;
}
