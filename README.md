# cobra

The Cobra game engine is a C++ game engine based on a very old and lost version made in Python. The main goal for this engine is to be used as a Python library, due to being faster and more high-level then PyGame.

You need SDL2 and SDL2-TTF to compile.

If you will be compiling, use g++ main.cpp -lSDL2 -lSDL2Main -lSDL2_ttf --std=c++11.

Always keep #define SDL_MAIN_HANDLED at the top in main.cpp and always include "cobra.cpp"!

