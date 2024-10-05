#pragma once

#include <unordered_set>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"
namespace engine::ecs {

class EntityCollection final {
 public:
  EntityCollection() = default;

  class Iterator final {
   public:
    Iterator() = default;

   private:
    EntityID parent_id_;
    std::unordered_set<EntityID, EntityID::Hash> children_ids_;

    ComponentCollection entity_data_;
  };

 private:
};
}  // namespace engine::ecs