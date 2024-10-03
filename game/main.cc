#include <exception>
#include <iostream>

#include "ecs/component.h"
using engine::ecs::Component;

struct Position final : public Component {
 public:
  Position() = default;
  Position(float x, float y) : x_coord(x), y_coord(y) {}

  float x_coord{}, y_coord{};
};

struct Velocity final : public Component {
 public:
  Velocity() = default;
  Velocity(float x_comp, float y_comp) : d_x(x_comp), d_y(y_comp) {}

  float d_x{}, d_y{};
};

#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

int main() {
  try {
    ComponentCollection collection;
    collection.TryEmplace<Position>(10, 12);
    auto position = collection.Get<Position>();
    if (auto tmp = position.lock()) {
      std::cout << "Position: {" << tmp->x_coord << ", " << tmp->y_coord << "}\n";
    }
    std::cout << std::boolalpha << collection.Has<Position>() << "\n";
  } catch (const std::exception& err) {
    std::cout << err.what() << "\n";
    return -1;
  }
  return 0;
}