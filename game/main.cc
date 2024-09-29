#include <exception>
#include <iostream>

#include "raylib.h"

int main() {
  try {
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_width, "Hello, World!");

    while (!WindowShouldClose()) {
      BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);

      EndDrawing();
    }

    CloseWindow();

  } catch (const std::exception& err) {
    std::cout << err.what() << "\n";
    return -1;
  }
  return 0;
}