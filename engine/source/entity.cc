#include "ecs/entity.h"
using engine::ecs::Entity;

#include "ecs/entity-id.h"
using engine::ecs::EntityID;

#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

EntityID Entity::GetParentID() const noexcept { return parent_id_; }

void Entity::RememberParent(const EntityID& new_parent_id) { parent_id_ = new_parent_id; }

bool Entity::IsChildOf(const EntityID& entity_id) const noexcept { return parent_id_ == entity_id; }

std::unordered_set<EntityID, EntityID::Hash> Entity::GetChildrenIDs() const noexcept { return children_ids_; }

bool Entity::RememberChild(const EntityID& new_child_id) {
  bool was_remembered{false};
  if (!children_ids_.contains(new_child_id)) {
    was_remembered = children_ids_.insert(new_child_id).second;
  }
  return was_remembered;
}

bool Entity::ForgetChild(const EntityID& target_child_id) { return children_ids_.erase(target_child_id) > 0; }

void Entity::ForgetChildren() { children_ids_.clear(); }

const ComponentCollection& Entity::GetComponents() const noexcept { return data_; }

ComponentCollection& Entity::GetComponents() noexcept { return data_; }