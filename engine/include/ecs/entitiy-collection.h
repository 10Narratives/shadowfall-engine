#pragma once

#include <functional>
#include <unordered_map>

#include "ecs/component-collection.h"
#include "ecs/entitiy-relations.h"
#include "ecs/entity-id.h"

namespace engine::ecs {

using ecs_data = std::pair<EntityRelations, ComponentCollection>;
using ecs_predicate = std::function<bool(const ecs_data&)>;

class EntityCollection final {
 public:
  EntityCollection() = default;

  [[nodiscard]] inline bool Empty() const noexcept { return inner_entities_.empty(); }

  [[nodiscard]] inline std::size_t Size() const noexcept { return inner_entities_.size(); }

  void Clear() { inner_entities_.clear(); }

  [[maybe_unused]] std::pair<EntityID, bool> Insert(const ComponentCollection& entity_data,
                                                    const EntityID& parent_id = EntityID::GetRootID());

  [[maybe_unused]] std::pair<EntityID, bool> Insert(ComponentCollection&& entity_data,
                                                    const EntityID& parent_id = EntityID::GetRootID());

  [[maybe_unused]] bool InsertRange(const EntityCollection& collection,
                                    const EntityID& parent_id = EntityID::GetRootID());

  [[maybe_unused]] bool InsertRange(EntityCollection&& collection, const EntityID& parent_id = EntityID::GetRootID());

  [[maybe_unused]] bool Erase(const EntityID& target_id);

  [[maybe_unused]] bool EraseIf(const ecs_predicate& predicate);

  [[nodiscard]] const ecs_data& At(const EntityID& id) const;

  [[nodiscard]] ecs_data& At(const EntityID& id);

  [[nodiscard]] EntityCollection Where(const ecs_predicate& predicate);

 private:
  std::unordered_map<EntityID, ecs_data, EntityID::Hash> inner_entities_;
};

}  // namespace engine::ecs