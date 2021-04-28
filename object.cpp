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
  double mass;
  double damping = 1;
  Color color;
  bool centered;
  bool fill;

  Object() {};

  Object(Vector2 nposition, Vector2 nsize, double nmass, Color ncolor, bool centeredn = true, bool filln = true) {
    position = nposition;
    size = nsize;
    color = ncolor;
    fill = filln;
    centered = centeredn;
    mass = nmass;
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

  Object clone() {
    Object clone(position, size, mass, color, centered, fill);
    clone.velocity = velocity;
    clone.damping = damping;
    return clone;
  };

};
