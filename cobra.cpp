#define SDL_MAIN_HANDLED

#include "vector2.cpp"
#include "color.cpp"
#include "object.cpp"
#include "particle.cpp"
#include "text.cpp"
#include "sound_sfx.cpp"
#include "physics_engine.cpp"
#include "camera.cpp"
#include "scene.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "SDL.h"

int random_int(int min, int max) {
  return min + (rand() % (max - min + 1));
};

double lerp(double num, double target, double divider) {
  return num * (1 - divider) + target * divider;
};

double clamp(double num, double min, double max) {
  if (num < min) {
    num = min;
  };
  if (num > max) {
    num = max;
  };
  return num;
};

double d2r(double degree) {
  return degree / 57.2958;
}

double r2d(double radian) {
  return radian * 57.2958;
}

namespace Cobra {
  SDL_Window* window;
  int objects_free_index = 0;
  int texts_free_index = 0;
  Color bgcolor;
  double frame_start;
  PhysicsEngine physics_engine;
  SDL_Renderer* renderer;
  Camera camera;
  Scene* scene;
  Scene* to_set_scene;
  Vector2 window_size;
  const Uint8 *keyboard;
  Vector2 mouse_position;
  double delta = .016;
  bool running = true;

  void init(Color bg_color, Vector2 win_size) {
    bgcolor = bg_color;
    window_size = win_size;
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Cobra Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_size.x, win_size.y, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  };

  void set_camera(Camera new_cam) {
    camera = new_cam;
  };

  void quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
  }

  void wait(double time) {
    SDL_Delay(time * 1000);
  };

  void set_fullscreen(bool mode) {
    SDL_SetWindowFullscreen(window, mode);
  };

  void set_scene(Scene* new_scene) {
    if (running) {to_set_scene = new_scene;};
  };

  bool detect_collision(Object* obj1, Object* obj2) {
    if (obj1->centered == true && obj2->centered == true) {
      return physics_engine.detect_collision_centered(obj1, obj2);
    };
    if (obj1->centered == false && obj2->centered == false) {
      return physics_engine.detect_collision(obj1, obj2);
    };
    return false;
  };

  bool detect_collision(Object obj1, Object obj2) {
    if (obj1.centered == true && obj2.centered == true) {
      return physics_engine.detect_collision_centered(&obj1, &obj2);
    };
    if (obj1.centered == false && obj2.centered == false) {
      return physics_engine.detect_collision(&obj1, &obj2);
    };
    return false;
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

  void handle_keyboard() {
      SDL_PumpEvents();
      const Uint8* keyboard_tmp = SDL_GetKeyboardState(0);
      keyboard = keyboard_tmp;
  };

  bool handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_MOUSEMOTION) {
        mouse_position.x = event.motion.x;
        mouse_position.y = event.motion.y;
      };
      if (event.type == SDL_QUIT) {
        quit();
        return true;
      };
    };
    return false;
  };

  void handle_physics() {
    for (size_t index = 0; index < scene->objects.size(); index++) {
      Object* curr_obj = scene->objects[index];
      curr_obj->update_velocity(delta);
    };
    for (size_t index = 0; index < scene->particles.size(); index++) {
      Particle* curr_part = scene->particles[index];
      curr_part->update(delta);
      if (curr_part->life <= 0) {
        scene->particles.erase(scene->particles.begin() +index);
        delete curr_part;
      };
    };
  };

  void render_particle(Particle* curr_part) {
    SDL_SetRenderDrawColor(renderer, curr_part->color.r, curr_part->color.g, curr_part->color.b, curr_part->color.a);
    SDL_Rect rect;
    rect.x = curr_part->position.x - (curr_part->size / 2) - camera.position.x;
    rect.y = curr_part->position.y - (curr_part->size / 2) - camera.position.y;
    rect.w = curr_part->size;
    rect.h = curr_part->size;
    SDL_RenderFillRect(renderer, &rect);
  }

  void render_object(Object* curr_obj) {
    if (curr_obj->texture_dir != "") {
      if (!curr_obj->texture_setup) {
        curr_obj->setup_texture(renderer);
      };
      SDL_Rect objRect;

      if (curr_obj->centered) {
        objRect.x = curr_obj->position.x - curr_obj->size.x / 2 - camera.position.x;
        objRect.y = curr_obj->position.y - curr_obj->size.y / 2 - camera.position.y;
      } else {
        objRect.x = curr_obj->position.x - camera.position.x;
        objRect.y = curr_obj->position.y - camera.position.y;
      };
      objRect.w = curr_obj->surface->w;
      objRect.h = curr_obj->surface->h;

      SDL_RenderCopy(renderer, curr_obj->texture, NULL, &objRect);
    } else {
      SDL_SetRenderDrawColor(renderer, curr_obj->color.r, curr_obj->color.g, curr_obj->color.b, curr_obj->color.a);
      SDL_Rect rect;
      if (curr_obj->centered) {
        rect.x = curr_obj->position.x - (curr_obj->size.x / 2) - camera.position.x;
        rect.y = curr_obj->position.y - (curr_obj->size.y / 2) - camera.position.y;
      } else {
        rect.x = curr_obj->position.x - camera.position.x;
        rect.y = curr_obj->position.y - camera.position.y;
      };
      rect.w = curr_obj->size.x;
      rect.h = curr_obj->size.y;
      if (curr_obj->fill) {
        SDL_RenderFillRect(renderer, &rect);
      } else {
        SDL_RenderDrawRect(renderer, &rect);
      };
    };
  };

  void render_text(Text* curr_text) {
    SDL_Color textColor = { (Uint8) curr_text->color.r, (Uint8) curr_text->color.g, (Uint8) curr_text->color.b, (Uint8) curr_text->color.a };
    SDL_Surface* textSurface = TTF_RenderText_Solid(curr_text->font, curr_text->text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;

    if (curr_text->centered) {
      textRect.x = curr_text->position.x - textSurface->w / 2 - camera.position.x;
      textRect.y = curr_text->position.y - textSurface->h / 2 - camera.position.y;
    } else {
      textRect.x = curr_text->position.x - camera.position.x;
      textRect.y = curr_text->position.y - camera.position.y;
    };
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
  };

  void render() {
      SDL_SetRenderDrawColor(renderer, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
      SDL_RenderClear(renderer);
      int z_min = 0;
      int z_max = 0;
      for (size_t i = 0; i < scene->particles.size(); i++) {
        if (scene->particles[i]->z_index < z_min) {
          z_min = scene->particles[i]->z_index;
        };
        if (scene->particles[i]->z_index > z_max) {
          z_max = scene->particles[i]->z_index;
        };
      };
      for (size_t i = 0; i < scene->objects.size(); i++) {
        if (scene->objects[i]->z_index < z_min) {
          z_min = scene->objects[i]->z_index;
        };
        if (scene->objects[i]->z_index > z_max) {
          z_max = scene->objects[i]->z_index;
        };
      };
      for (size_t i = 0; i < scene->texts.size(); i++) {
        if (scene->texts[i]->z_index < z_min) {
          z_min = scene->texts[i]->z_index;
        };
        if (scene->texts[i]->z_index > z_max) {
          z_max = scene->texts[i]->z_index;
        };
      };
      for (size_t z_index = 0; z_index < (1 + z_max + -z_min); z_index++) {
        for (size_t index = 0; index < scene->particles.size(); index++) {
          if (scene->particles[index]->z_index == z_index + z_min) {
            Cobra::render_particle(scene->particles[index]);
          };
        };
        for (size_t index = 0; index < scene->objects.size(); index++) {
          if (scene->objects[index]->z_index == z_index + z_min) {
            Cobra::render_object(scene->objects[index]);
          };
        };
        for (size_t index = 0; index < scene->texts.size(); index++) {
          if (scene->texts[index]->z_index == z_index + z_min) {
            Cobra::render_text(scene->texts[index]);
          };
        };
      };
      SDL_RenderPresent(renderer);
    };

  void play_sfx(SFX sfx) {
    if (Mix_PlayingMusic() == 0) {
      Mix_PlayChannel( -1, sfx.sfx, 0 );
    };
  };

  void handle_all() {
    Cobra::start_frame();
    Cobra::handle_keyboard();
    Cobra::render();
    Cobra::handle_physics();
    Cobra::handle_events();
    bool game_running = !Cobra::handle_events();
    Cobra::scene->running = game_running;
    Cobra::running = game_running;
    Cobra::scene->main();
    Cobra::end_frame();
  };

  void mainloop() {
    Cobra::scene = Cobra::to_set_scene;
    while (running) {
      while (Cobra::scene->running) {
        handle_all();
      };
      if (Cobra::scene != Cobra::to_set_scene) {
        Cobra::scene = Cobra::to_set_scene;
        std::cout << "changed" << '\n';
      } else {
        quit();
        running = false;
      };
    };
    std::cout << "fin" << '\n';
  };
};
