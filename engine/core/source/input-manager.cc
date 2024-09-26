#include "core/input-manager.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

using engine::core::InputManager;

void InputManager::HandleInput(SDL_Window *window) {
  SDL_Event current_event;
  while (SDL_PollEvent(&current_event)) {
    if (current_event.type == SDL_EVENT_QUIT) {
      SDL_DestroyWindow(window);
    }
  }
}