#pragma once

#include <unordered_set>

#include "ecs/entity-id.h"
namespace engine::ecs {
struct EntityRelations final {
 public:
  EntityRelations() = default;

  EntityID parent_id{EntityID::GetRootID()};
  std::unordered_set<EntityID, EntityID::Hash> children_ids;
};
}  // namespace engine::ecs