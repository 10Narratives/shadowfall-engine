#pragma once

#include <unordered_set>

#include "ecs/entity-id.h"
namespace engine::ecs {
struct EntityRelations final {
 public:
  EntityRelations() = default;

  explicit EntityRelations(EntityID par_id) : parent_id(par_id) {}

  EntityRelations(EntityID par_id, const std::unordered_set<EntityID, EntityID::Hash>& children_ids)
      : parent_id(par_id), children_ids(children_ids) {}

  EntityID parent_id{EntityID::GetRootID()};
  std::unordered_set<EntityID, EntityID::Hash> children_ids;
};
}  // namespace engine::ecs