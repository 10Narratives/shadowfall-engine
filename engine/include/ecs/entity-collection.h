#pragma once

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <utility>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"

namespace engine::ecs {

using Predicate = std::function<bool(const ComponentCollection&)>;

class EntityCollection final {
 public:
  EntityCollection() = default;

  [[nodiscard]] std::size_t Size() const noexcept;

  [[nodiscard]] bool Empty() const noexcept;

  void Clear();

  [[maybe_unused]] std::pair<EntityID, bool> Insert(const ComponentCollection& entity_data,
                                                    const EntityID& parent_id = EntityID::GetRootID());

  [[maybe_unused]] std::pair<EntityID, bool> Insert(ComponentCollection&& entity_data,
                                                    const EntityID& parent_id = EntityID::GetRootID());

  [[maybe_unused]] bool Erase(const EntityID& target_id);

  [[maybe_unused]] bool EraseIf(const Predicate& predicate);

  [[nodiscard]] ComponentCollection Extract(const EntityID& target_id);

  [[nodiscard]] const ComponentCollection& At(const EntityID& entity_id) const;
  [[nodiscard]] ComponentCollection& At(const EntityID& entity_id);

  [[nodiscard]] bool Contains(const EntityID& target_id) const noexcept;

 private:
  std::unordered_map<EntityID, ComponentCollection, EntityID::Hash> inner_entities_;
};

}  // namespace engine::ecs