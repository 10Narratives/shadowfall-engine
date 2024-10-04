#pragma once

#include <unordered_set>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"

namespace engine::ecs {
class EntityNode final {
 public:
  EntityNode() = default;

  [[nodiscard]] EntityID GetParentID() const noexcept;
  void ResetParentID(const EntityID& new_parent_id);

  [[nodiscard]] std::unordered_set<EntityID, EntityID::Hash> GetChildrenIDs() const noexcept;

  [[maybe_unused]] bool RememberAsChild(const EntityID& entity_id);
  [[maybe_unused]] bool ForgetChild(const EntityID& entity_id);
  [[nodiscard]] bool Knows(const EntityID& child_id) const noexcept;

  [[nodiscard]] const ComponentCollection& GetComponents() const noexcept;
  [[nodiscard]] ComponentCollection& GetComponents() noexcept;

 private:
  EntityID parent_id_{EntityID::GetRootID()};
  std::unordered_set<EntityID, EntityID::Hash> children_ids_;

  ComponentCollection entity_components_;
};
}  // namespace engine::ecs