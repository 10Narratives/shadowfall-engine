#include <memory>

#include "ecs/component-base.h"
using engine::ecs::ComponentBase;

struct Position final : public ComponentBase {
 public:
  Position() = default;
  Position(float x, float y) : x_coord(x), y_coord(y) {}
  ~Position() override = default;
  Position(const Position& other) = default;
  Position& operator=(const Position& other) = default;

  float x_coord{}, y_coord{};
};

struct Velocity final : public ComponentBase {
 public:
  Velocity() = default;
  Velocity(float x, float y) : x_comp(x), y_comp(y) {}
  ~Velocity() override = default;
  Velocity(const Velocity& other) = default;
  Velocity& operator=(const Velocity& other) = default;

  float x_comp{}, y_comp{};
};

#include "ecs/tag-component.h"
using engine::ecs::TagComponent;

struct MoveableMarker final : public TagComponent {};

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

// TODO(narratives): Make test case with constructors and copy assignment.
// TODO(narratives): Make more scenarios of testing.

TEST_CASE("ComponentCollection Manipulation Methods") {
  ComponentCollection collection;
  SECTION("Method Emplace()") {
    REQUIRE(collection.Size() == 0);
    REQUIRE(collection.Empty() == true);
    collection.Emplace<Position>(10, 10);
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);
    collection.Emplace<Velocity>(1, 1);
    REQUIRE(collection.Size() == 2);
    REQUIRE(collection.Empty() == false);
    collection.Emplace<MoveableMarker>();
    REQUIRE(collection.Size() == 3);
    REQUIRE(collection.Empty() == false);
  }
  SECTION("Method Erase()") {
    collection.Emplace<Position>(10, 10);
    collection.Emplace<Velocity>(1, 1);
    collection.Emplace<MoveableMarker>();
    REQUIRE(collection.Size() == 3);
    REQUIRE(collection.Empty() == false);
    collection.Erase<MoveableMarker>();
    REQUIRE(collection.Size() == 2);
    REQUIRE(collection.Empty() == false);
  }
  SECTION("Method Extract()") {
    collection.Emplace<Position>(10, 10);
    collection.Emplace<Velocity>(1, 1);
    REQUIRE(collection.Size() == 2);
    REQUIRE(collection.Empty() == false);
    auto component = collection.Extract<Position>();
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);
    auto casted_position = std::dynamic_pointer_cast<Position>(component);
    REQUIRE(casted_position->x_coord == 10);
    REQUIRE(casted_position->y_coord == 10);
  }
  SECTION("Method Get()") {
    collection.Emplace<Velocity>(1, 1);
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);
    auto gotten_velocity = collection.Get<Velocity>();
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);
    if (auto tmp = gotten_velocity.lock()) {
      REQUIRE(tmp->x_comp == 1);
      REQUIRE(tmp->y_comp == 1);
    }
  }
}

TEST_CASE("ComponentCollection Query Methods") {
  ComponentCollection collection;
  collection.Emplace<Position>(10, 10);
  collection.Emplace<Velocity>(1, 1);
  SECTION("Method HasAll()") { REQUIRE(collection.HasAll<Position, Velocity>() == true); }
  SECTION("Method HasAny()") { REQUIRE(collection.HasAny<Position, MoveableMarker>() == true); }
  SECTION("Method HasNoneOf()") { REQUIRE(collection.HasNoneOf<MoveableMarker>() == true); }
}