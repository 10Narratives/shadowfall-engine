#include "ecs/entity-collection.h"

#include <utility>
using engine::ecs::EntityCollection;

#include "ecs/entity-id.h"
using engine::ecs::EntityID;

// #include "ecs/entity-node.h"
// using engine::ecs::EntityNode;

#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

std::pair<EntityID, bool> EntityCollection::Insert(const ComponentCollection& entity_data, const EntityID& parent_id) {
  ComponentCollection entity_data_copy{entity_data};
  return Insert(std::move(entity_data_copy), parent_id);
}
