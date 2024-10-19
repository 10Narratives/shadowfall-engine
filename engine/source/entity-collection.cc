#include "ecs/entity-collection.h"
using engine::ecs::EntityCollection;

#include <cstddef>
// #include <utility>

// #include "ecs/component-collection.h"
// using engine::ecs::ComponentCollection;

// #include "ecs/entity-id.h"
// using engine::ecs::EntityID;

std::size_t EntityCollection::Size() const noexcept { return inner_entities_.size(); }

bool EntityCollection::Empty() const noexcept { return inner_entities_.empty(); }

void EntityCollection::Clear() { inner_entities_.clear(); }
