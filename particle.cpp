#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "SDL.h"

class Particle {

public:
  Vector2 position;
  double size;
  Vector2 velocity;
  double damping = 1;
  Color color;
  Color start_color;
  Color end_color;
  double lifespan;
  double life;
  int z_index = 0;

  Particle() {};

  Particle(Vector2 nposition, double nsize, Color nstart_color, Color nend_color, double nlifespan, int z_indexn = 0) {
    position = nposition;
    size = nsize;
    start_color = nstart_color;
    end_color = nend_color;
    size = nsize;
    lifespan = nlifespan;
    life = nlifespan;
    z_index = z_indexn;
  };

  Particle(const Particle& particle) {
    position = particle.position;
    size = particle.size;
    start_color = particle.start_color;
    end_color = particle.end_color;
    size = particle.size;
    lifespan = particle.lifespan;
    life = particle.lifespan;
    velocity = particle.velocity;
    damping = particle.damping;
    z_index = particle.z_index;
  }

  void apply_impulse(double x, double y) {
    velocity.x += x;
    velocity.y += y;
  };

  void apply_impulse(Vector2 impulse) {
    velocity += impulse;
  };

  void update(double delta) {
    position += velocity * delta;
    velocity *= damping;
    life -= delta;
    double divider = life / lifespan;
    color.r = (start_color.r * divider) + (end_color.r * (1 - divider));
    color.g = (start_color.g * divider) + (end_color.g * (1 - divider));
    color.b = (start_color.b * divider) + (end_color.b * (1 - divider));
    color.a = (start_color.a * divider) + (end_color.a * (1 - divider));
  };

  Particle clone() {
    Particle clone(position, size, start_color, end_color, lifespan, z_index);
    clone.velocity = velocity;
    clone.damping = damping;
    return clone;
  };

};
