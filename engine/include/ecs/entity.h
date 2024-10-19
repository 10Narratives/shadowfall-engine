#pragma once

#include <unordered_set>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"
namespace engine::ecs {

class Entity final {
 public:
  Entity() = default;

  [[nodiscard]] EntityID GetParentID() const noexcept;
  void RememberParent(const EntityID& new_parent_id);
  [[nodiscard]] bool IsChildOf(const EntityID& entity_id) const noexcept;

  [[nodiscard]] std::unordered_set<EntityID, EntityID::Hash> GetChildrenIDs() const noexcept;
  [[maybe_unused]] bool RememberChild(const EntityID& new_child_id);
  [[maybe_unused]] bool ForgetChild(const EntityID& target_child_id);
  void ForgetChildren();
  [[nodiscard]] bool IsParentOf(const EntityID& target_child_id) const noexcept;

  [[nodiscard]] const ComponentCollection& GetComponents() const noexcept;
  [[nodiscard]] ComponentCollection& GetComponents() noexcept;

 private:
  EntityID parent_id_{EntityID::GetRootID()};                  // ID of parent entity.
  std::unordered_set<EntityID, EntityID::Hash> children_ids_;  // ID of childrens entity.

  ComponentCollection data_;  // Inner components of this entity.
};

}  // namespace engine::ecs