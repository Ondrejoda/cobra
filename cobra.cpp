#define SDL_MAIN_HANDLED

#include "vector2.cpp"
#include "color.cpp"
#include "object.cpp"
#include "text.cpp"
#include "physics_engine.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <SDL2/SDL_ttf.h>

#include "SDL.h"

class Engine {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int objects_free_index = 0;
  int texts_free_index = 0;
  Color bgcolor;
  double frame_start;
  PhysicsEngine physics_engine;

public:
  Object* objects[8192];
  Text* texts[8192];
  Vector2 window_size;
  const Uint8 *keyboard;
  double delta = .016;


  Engine(Color bg_color, Vector2 win_size) {
    bgcolor = bg_color;
    window_size = win_size;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow("Cobra Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_size.x, win_size.y, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  };

  void quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  bool detect_collision(Object obj1, Object obj2) {
    if (obj1.centered == true && obj2.centered == true) {
      return physics_engine.detect_collision_centered(obj1, obj2);
    };
    if (obj1.centered == false && obj2.centered == false) {
      return physics_engine.detect_collision(obj1, obj2);
    };
    return false;
  };

  int add_object(Object* obj) {
    objects[objects_free_index] = obj;
    objects_free_index++;
    return objects_free_index - 1;
  };

  int add_text(Text* text) {
    texts[texts_free_index] = text;
    texts_free_index++;
    return texts_free_index - 1;
  };

  Object* get_object(int index) {
    return objects[index];
  };

  double time() {
    return SDL_GetTicks();
  };

  double start_frame() {
    frame_start = SDL_GetTicks();
  };

  double end_frame() {
    delta = (SDL_GetTicks() - frame_start) / 1000;
  };

  void set_object(int index, Object* obj) {
    objects[index] = obj;
  };

  void handle_keyboard() {
      SDL_PumpEvents();
      const Uint8* keyboard_tmp = SDL_GetKeyboardState(0);
      keyboard = keyboard_tmp;
  };

  void handle_physics() {
    for (size_t index = 0; index < objects_free_index; index++) {
      Object* curr_obj = objects[index];
      curr_obj->update_velocity(delta);
    };
  };

  bool handle_exit() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit();
        return true;
      };
    };
    return false;
  };

  bool handle_all() {
    render();
    handle_physics();
    handle_keyboard();
    return handle_exit();
  }

  void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for (size_t index = 0; index < objects_free_index; index++) {
      Object* curr_obj = objects[index];
      SDL_SetRenderDrawColor(renderer, curr_obj->color.r, curr_obj->color.g, curr_obj->color.b, curr_obj->color.a);
      SDL_Rect rect;
      if (curr_obj->centered) {
        rect.x = curr_obj->position.x - (curr_obj->size.x / 2);
        rect.y = curr_obj->position.y - (curr_obj->size.y / 2);
      } else {
        rect.x = curr_obj->position.x;
        rect.y = curr_obj->position.y;
      };
      rect.w = curr_obj->size.x;
      rect.h = curr_obj->size.y;
      if (curr_obj->fill) {
        SDL_RenderFillRect(renderer, &rect);
      } else {
        SDL_RenderDrawRect(renderer, &rect);
      };
    };
    for (size_t index = 0; index < texts_free_index; index++) {
      Text* curr_text = texts[index];
      SDL_Color textColor = { (Uint8) curr_text->color.r, (Uint8) curr_text->color.g, (Uint8) curr_text->color.b, (Uint8) curr_text->color.a };
      SDL_Surface* textSurface = TTF_RenderText_Solid(curr_text->font, curr_text->text.c_str(), textColor);
      SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

      SDL_Rect textRect;
      textRect.x = curr_text->position.x;
      textRect.y = curr_text->position.y;
      textRect.w = textSurface->w;
      textRect.h = textSurface->h;
      SDL_FreeSurface(textSurface);
      SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    };
    SDL_RenderPresent(renderer);
  };
};
