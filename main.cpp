#define SDL_MAIN_HANDLED

#include "cobra.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>

#include "SDL.h"

int main(int argc, char const *argv[]) {
  Engine cobra(Color(0, 0, 0, 255), Vector2(800, 600));

  Object box(Vector2(100, 100), Vector2(50, 50), 10, Color(255, 0, 0, 255));
  box.damping = .997;
  cobra.add_object(&box);

  while (true) {
    cobra.start_frame();
    if (cobra.handle_all()) {
      break;
    };
    if (cobra.keyboard[SDL_SCANCODE_LEFT]) {
      box.apply_impulse(-2, 0);
    };
    if (cobra.keyboard[SDL_SCANCODE_RIGHT]) {
      box.apply_impulse(2, 0);
    };
    if (cobra.keyboard[SDL_SCANCODE_UP]) {
      box.apply_impulse(0, -2);
    };
    if (cobra.keyboard[SDL_SCANCODE_DOWN]) {
      box.apply_impulse(0, 2);
    };
    cobra.end_frame();
  }
  return 0;
};
