#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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

  Vector2 operator+(Vector2 other) {
    return Vector2(x + other.x, y + other.y);
  };

  Vector2 operator-(Vector2 other) {
    return Vector2(x - other.x, y - other.y);
  };

  Vector2 operator*(Vector2 other) {
    return Vector2(x * other.x, y * other.y);
  };

  Vector2 operator/(Vector2 other) {
    return Vector2(x / other.x, y / other.y);
  };

  Vector2 operator+(double num) {
    return Vector2(x + num, y + num);
  };

  Vector2 operator-(double num) {
    return Vector2(x - num, y - num);
  };

  Vector2 operator*(double num) {
    return Vector2(x * num, y * num);
  };

  Vector2 operator/(double num) {
    return Vector2(x / num, y / num);
  };

  void operator+=(Vector2 other) {
    x += other.x;
    y += other.y;
  };

  void operator-=(Vector2 other) {
    x -= other.x;
    y -= other.y;
  };

  void operator*=(Vector2 other) {
    x *= other.x;
    y *= other.y;
  };

  void operator/=(Vector2 other) {
    x /= other.x;
    y /= other.y;
  };

  void operator+=(double num) {
    x += num;
    y += num;
  };

  void operator-=(double num) {
    x -= num;
    y -= num;
  };

  void operator*=(double num) {
    x *= num;
    y *= num;
  };

  void operator/=(double num) {
    x /= num;
    y /= num;
  };

  bool operator==(Vector2 other) {
    return x == other.x && y == other.y;
  };

  bool operator!=(Vector2 other) {
    return !(x == other.x && y == other.y);
  };

  std::string str() {
    return std::to_string((int) x) + ", " + std::to_string(y);
  }
};
