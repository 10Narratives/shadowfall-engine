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

#include "ecs/archetype.h"
using engine::ecs::Archetype;

using Moveable = Archetype<MoveableMarker, Position, Velocity>;

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

TEST_CASE("Archetype methods") {
  ComponentCollection collection;
  SECTION("Method CreateInstance()") {
    collection = Moveable::CreateInstance();
    REQUIRE(collection.HasAll<MoveableMarker, Position, Velocity>() == true);
  }
  SECTION("Method IsPresentedIn()") {
    collection = Moveable::CreateInstance();
    REQUIRE(Moveable::IsPresentedIn(collection) == true);
  }
  SECTION("Method Supplement()") {
    Moveable::Supplement(collection);
    REQUIRE(Moveable::IsPresentedIn(collection) == true);
  }
}