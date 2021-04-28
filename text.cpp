#define SDL_MAIN_HANDLED


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>

#include "SDL.h"

class Text {

public:
  Vector2 position;
  Color color;
  std::string text = "";
  TTF_Font* font;


  Text() {};

  Text(std::string textn, std::string font_dir, double font_size, Vector2 positionn, Color colorn) {
    position = positionn;
    color = colorn;
    text = textn;
    font = TTF_OpenFont(font_dir.c_str(), font_size);
  };


};
