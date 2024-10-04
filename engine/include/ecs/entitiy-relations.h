#pragma once

#include <unordered_set>
#include <utility>

#include "ecs/entity-id.h"
namespace engine::ecs {
struct EntityRelations final {
 public:
  EntityRelations() = default;
  explicit EntityRelations(EntityID parent_id) : parent_id(std::move(parent_id)) {}

  EntityID parent_id{EntityID::GetRootID()};
  std::unordered_set<EntityID, EntityID::Hash> children_ids;
};
}  // namespace engine::ecs