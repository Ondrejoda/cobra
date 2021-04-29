#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "SDL.h"

class Color {

public:
  double r = 0;
  double g = 0;
  double b = 0;
  double a = 0;

  Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
  };

  Color(double nr, double ng, double nb, double na) {
    r = nr;
    g = ng;
    b = nb;
    a = na;
  };
};
