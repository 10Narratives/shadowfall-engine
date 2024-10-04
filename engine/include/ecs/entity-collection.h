#pragma once

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"
#include "ecs/entity-node.h"

namespace engine::ecs {

using Predicate = std::function<bool(const EntityNode&)>;

class EntityCollection final {
 public:
  EntityCollection() = default;

  [[nodiscard]] std::size_t Size() const noexcept;
  [[nodiscard]] bool Empty() const noexcept;

  void Clear();

  // Insertion of an entity node
  [[maybe_unused]] std::pair<EntityID, bool> Insert(const ComponentCollection& entity_data,
                                                    const EntityID& parent_id = EntityID::GetRootID());
  [[maybe_unused]] std::pair<EntityID, bool> Insert(ComponentCollection&& entity_data,
                                                    const EntityID& parent_id = EntityID::GetRootID());

  // Moves entities from source to this collection
  void MoveTo(EntityCollection& source, const EntityID& parent_id = EntityID::GetRootID());
  void MoveTo(EntityCollection&& source, const EntityID& parent_id = EntityID::GetRootID());

  // Erasing of an entity and its children
  [[maybe_unused]] bool Erase(const EntityID& target_id);

  // Erasing of entities which correspond to the predicate
  [[maybe_unused]] bool EraseIf(const Predicate& predicate);

  // Extracting of an entity node
  [[nodiscard]] EntityNode Extract(const EntityID& entity_id);

  // Access to component collection by entity id
  [[nodiscard]] const ComponentCollection& At(const EntityID& entity_id) const;
  [[nodiscard]] ComponentCollection& At(const EntityID& entity_id);

  // Finding an entity bu its id
  [[nodiscard]] const EntityNode& Find(const EntityID& id) const;
  [[nodiscard]] EntityNode& Find(const EntityID& id);

  // Getting a range of entities by some criteria
  [[nodiscard]] std::vector<EntityID> Select(const Predicate& predicate) const noexcept;

  // Checks if entity id is in use into this collection
  [[nodiscard]] bool Contains(const EntityID& entity_id) const noexcept;

 private:
  std::unordered_map<EntityID, EntityNode, EntityID::Hash> inner_entities_;
};

}  // namespace engine::ecs