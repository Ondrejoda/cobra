#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "SDL.h"

class Scene {
public:
  bool running = true;
  std::vector<Object*> objects;
  std::vector<Particle*> particles;
  std::vector<Text*> texts;

  void add_object(Object* obj) {
    objects.push_back(obj);
  };

  void add_object(Object obj) {
    objects.push_back(new Object(obj));
  };

  void add_particle(Particle part) {
    particles.push_back(new Particle(part));
  };

  void add_particle(Particle* part) {
    particles.push_back(part);
  };

  void add_text(Text* text) {
    texts.push_back(text);
  };


// here's the main() definition
  void main() {};
};
