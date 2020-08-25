#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#else
#include <GL/glu.h>
#endif

#include <SDL_opengl.h>

#include <iostream>
#include <string>

#include <bitset>

#include "CLI/CLI.hpp"

#include "gameboy.h"

int main(int argc, char *argv[])
{
  CLI::App app;

  std::string rom = "Tetris.gb";
  app.add_option("-r,--rom,rom", rom, "ROM to load");

  bool debug = false;
  app.add_option("-d,--debug", debug, "Enable debug window");

  CLI11_PARSE(app, argc, argv);

  //The window we'll be rendering to
  SDL_Window *window = NULL;

  //The surface contained by the window
  SDL_Surface *screenSurface = NULL;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  //Create window
  window = SDL_CreateWindow("GameBoy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, OUTPUT_WIDTH * 2, OUTPUT_HEIGHT * 2, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
  if (renderer == NULL)
  {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_RenderSetScale(renderer, 2, 2);

  GameBoy gameboy(rom, renderer);

  gameboy.run();

  //Destroy window
  SDL_DestroyWindow(window);

  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}
