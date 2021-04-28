#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "SDL.h"

class Vector2 {

public:
  double x = 0;
  double y = 0;

  Vector2() {
    x = 0;
    y = 0;
  };

  Vector2(double nx, double ny) {
    x = nx;
    y = ny;
  };
};
