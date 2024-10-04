#include "ecs/entitiy-node.h"
using engine::ecs::EntityNode;

#include "ecs/entity-id.h"
using engine::ecs::EntityID;

EntityID EntityNode::GetParentID() const noexcept { return parent_id_; }

void EntityNode::ResetParentID(const EntityID& new_parent_id) { parent_id_ = new_parent_id; }

std::unordered_set<EntityID, EntityID::Hash> EntityNode::GetChildrenIDs() const noexcept { return children_ids_; }

bool EntityNode::RememberAsChild(const EntityID& entity_id) {
  bool was_remembered{false};
  auto iter = children_ids_.find(entity_id);
  if (iter == children_ids_.end()) {
    children_ids_.insert(entity_id);
    was_remembered = true;
  }
  return was_remembered;
}

bool EntityNode::ForgetChild(const EntityID& entity_id) {
  bool was_forgotten{false};
  auto iter = children_ids_.find(entity_id);
  if (iter != children_ids_.end()) {
    children_ids_.erase(iter);
    was_forgotten = true;
  }
  return was_forgotten;
}

bool EntityNode::Knows(const EntityID& child_id) const noexcept { return children_ids_.contains(child_id); }