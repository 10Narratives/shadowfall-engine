#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

#include <iostream>

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Can not initialize SDL3 library.\n";
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow("Dungeon Legends", 500, 500, SDL_WINDOW_MAXIMIZED);
  if (!window) {
    std::cerr << "Cant not initialize SDL_Window\n";
    return -1;
  }

  SDL_Surface* window_surface = SDL_GetWindowSurface(window);

  bool is_open = true;
  SDL_Event event;
  while (is_open) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        is_open = false;
      }
    }

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}