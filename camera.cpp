#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "SDL.h"

class Camera {
public:
  Vector2 position;

  Camera() {};

  Camera(Vector2 nposition) {
    position = nposition;
  };

  Camera(double x, double y) {
    position.x = x;
    position.y = y;
  };
};
