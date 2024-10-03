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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// #include "ecs/component-collection.h"
// using engine::ecs::ComponentCollection;

TEST_CASE("Methods of ComponentCollection") {
  SECTION("Emplace()") {}
  SECTION("TryEmplace()") {}
  SECTION("Erase()") {}
  SECTION("Extract()") {}
  SECTION("Has()") {}
  SECTION("HasAll()") {}
  SECTION("HasAny()") {}
}
