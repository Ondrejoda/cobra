#define SDL_MAIN_HANDLED

#include "vector2.cpp"
#include "object.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>

#include "SDL.h"

class PhysicsEngine {
  
  PhysicsEngine() {};

  bool detect_collision_centered(Object obj1, Object obj2) {
    if (obj1.position.x - obj1.size.x / 2 < obj2.position.x + obj2.size.x / 2 &&
      obj1.position.x + obj1.size.x / 2 > obj2.position.x - obj2.size.x / 2 &&
      obj1.position.y - obj1.size.y / 2 < obj2.position.y + obj2.size.y / 2 &&
      obj1.position.y + obj1.size.y / 2 > obj2.position.y - obj2.size.x / 2) {
      return true;
    };
    return false;
  };
  bool detect_collision(Object obj1, Object obj2) {
    if (obj1.position.x < obj2.position.x + obj2.size.x &&
      obj1.position.x + obj1.size.x > obj2.position.x &&
      obj1.position.y < obj2.position.y + obj2.size.y &&
      obj1.position.y + obj1.size.y > obj2.position.y) {
      return true;
    };
    return false;
  };

};
