#define SDL_MAIN_HANDLED


#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "SDL.h"

class Object {

public:
  Vector2 position;
  Vector2 size;
  Vector2 velocity;
  double damping = 1;
  Color color;
  bool centered;
  bool fill;
  std::string name = "";

  Object() {};

  Object(std::string n_name, Vector2 nposition, Vector2 nsize, Color ncolor, bool centeredn = true, bool filln = true) {
    position = nposition;
    size = nsize;
    color = ncolor;
    name = n_name;
    fill = filln;
    centered = centeredn;
  };

  void apply_impulse(double x, double y) {
    velocity.x += x;
    velocity.y += y;
  };

  void move(double x, double y) {
    position.x += x;
    position.y += y;
  };

  void update_velocity(double delta) {
    position.x += velocity.x * delta;
    position.y += velocity.y * delta;
    velocity.x *= damping;
    velocity.y *= damping;
  };

  bool is_colliding_with(Object obj) {
    if (position.x < obj.position.x + obj.size.x && position.x + size.x > obj.position.x && position.y < obj.position.y + obj.size.y && position.y + size.y > obj.position.y) {
      return true;
    };
    return false;
  };

  bool is_colliding_with_centered(Object obj) {
    if (position.x - size.x / 2 < obj.position.x + obj.size.x / 2 &&
      position.x + size.x / 2 > obj.position.x - obj.size.x / 2 &&
      position.y - size.y / 2 < obj.position.y + obj.size.y / 2 &&
      position.y + size.y / 2 > obj.position.y - obj.size.x / 2) {
      return true;
    };
    return false;
  };

  Object clone() {
    Object clone(name, position, size, color, centered, fill);
    clone.velocity = velocity;
    clone.damping = damping;
    return clone;
  };

};
