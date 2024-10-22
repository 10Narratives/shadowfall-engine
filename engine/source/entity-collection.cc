#include "ecs/entity-collection.h"

#include <vector>
using engine::ecs::EntityCollection;

#include <cstddef>
#include <utility>

#include "ecs/component-collection.h"
#include "ecs/entity.h"
using engine::ecs::ComponentCollection;
using engine::ecs::Entity;

#include "ecs/entity-id.h"
using engine::ecs::EntityID;

std::size_t EntityCollection::Size() const noexcept { return inner_entities_.size(); }

bool EntityCollection::Empty() const noexcept { return inner_entities_.empty(); }

void EntityCollection::Clear() { inner_entities_.clear(); }

std::pair<EntityID, bool> EntityCollection::Insert(const ComponentCollection& entity_data, const EntityID& parent_id) {
  ComponentCollection entity_data_copy = entity_data;
  return Insert(std::move(entity_data_copy), parent_id);
}

std::pair<EntityID, bool> EntityCollection::Insert(ComponentCollection&& entity_data, const EntityID& parent_id) {
  Entity new_entity;
  new_entity.RememberParent(parent_id);
  new_entity.SetComponents(std::move(entity_data));

  EntityID new_id;
  bool was_inserted = inner_entities_.insert({new_id, new_entity}).second;

  return {new_id, was_inserted};
}

std::pair<ComponentCollection, bool> EntityCollection::Extract(const EntityID& target_id) {
  ComponentCollection extracted_data;
  bool was_extracted{false};
  auto iter = inner_entities_.find(target_id);
  if (iter != inner_entities_.end()) {
    auto extracted_node = inner_entities_.extract(iter);
    extracted_data = extracted_node.mapped().CloneComponents();
    was_extracted = true;
  }
  return {extracted_data, false};
}

bool EntityCollection::Erase(const EntityID& target_id) {
  bool was_erased = false;
  if (inner_entities_.contains(target_id)) {
    auto children_ids = inner_entities_[target_id].GetChildrenIDs();
    for (const auto& child_id : children_ids) {
      Erase(child_id);
    }
    was_erased = inner_entities_.erase(target_id) > 0;
  }
  return was_erased;
}

bool EntityCollection::EraseIf(const Predicate& predicate) {
  bool was_erased = false;
  for (auto& [id, entity] : inner_entities_) {
    if (predicate(entity.GetComponents())) {
      was_erased |= inner_entities_.erase(id);
    }
  }
  return was_erased;
}

ComponentCollection& EntityCollection::At(const EntityID& entity_id) {
  return inner_entities_.at(entity_id).GetComponents();
}

const ComponentCollection& EntityCollection::At(const EntityID& entity_id) const {
  return inner_entities_.at(entity_id).GetComponents();
}

std::size_t EntityCollection::CountIf(const Predicate& predicate) {
  std::size_t counter = 0;
  for (const auto& [id, entity] : inner_entities_) {
    if (predicate(entity.GetComponents())) {
      counter++;
    }
  }
  return counter;
}

std::vector<EntityID> EntityCollection::Filter(const Predicate& predicate) const noexcept {
  std::vector<EntityID> total_ids{};
  for (const auto& [id, entity] : inner_entities_) {
    if (predicate(entity.GetComponents())) {
      total_ids.push_back(id);
    }
  }
  return total_ids;
}

bool EntityCollection::Contains(const EntityID& entity_id) const noexcept {
  return inner_entities_.contains(entity_id);
}