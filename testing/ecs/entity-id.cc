#define CATCH_CONFIG_MAIN
#include "ecs/entity-id.h"

#include "catch2/catch.hpp"
using engine::ecs::EntityID;

// TODO(narratives): Make more tests

TEST_CASE("EntityID constructor") {
  SECTION("Default constructor") {
    EntityID entity_id{};
    REQUIRE(entity_id.GetInnerData().empty() == false);
  }
}