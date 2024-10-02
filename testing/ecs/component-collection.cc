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

#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

TEST_CASE("Insertion into collection") {
  SECTION("Insert()") {
    ComponentCollection collection;
    engine::ecs::comp_ptr position = std::make_shared<Position>(10, 10);
    REQUIRE(collection.Insert<Position>(position) == true);
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);
    REQUIRE(collection.Insert<Position>(position) == false);
    auto stored_position = collection.Get<Position>();
    REQUIRE(stored_position->x_coord == 10);
    REQUIRE(stored_position->y_coord == 10);
  }
  SECTION("InsertOrAssign()") {
    ComponentCollection collection;
    engine::ecs::comp_ptr position = std::make_shared<Position>(10, 10);
    REQUIRE(collection.InsertOrAssign<Position>(position) == true);
  }
}
