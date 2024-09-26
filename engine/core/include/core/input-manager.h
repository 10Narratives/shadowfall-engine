#pragma once

#include <SDL3/SDL_video.h>
namespace engine::core {

class InputManager final {
 public:
  InputManager() = default;

  static void HandleInput(SDL_Window* window);
};
};  // namespace engine::core