#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "SDL.h"

class SFX {
public:
  Mix_Chunk* sfx;

  SFX() {};

  SFX(std::string file_path) {
    sfx = Mix_LoadWAV(file_path.c_str());
  };
};
