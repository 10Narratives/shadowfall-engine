#include "ecs/component-collection.h"

#include <memory>

#include "ecs/component-base.h"
using engine::ecs::ComponentCollection;

ComponentCollection::ComponentCollection(const ComponentCollection& other) {
  for (const auto& [key, component] : other.inner_components_) {
    auto component_copy = std::make_shared<ComponentBase>(*component);
    inner_components_.try_emplace(key, component_copy);
  }
}

ComponentCollection& ComponentCollection::operator=(const ComponentCollection& other) {
  if (this == &other) {
    return *this;
  }
  inner_components_.clear();
  for (const auto& [key, component] : other.inner_components_) {
    auto component_copy = std::make_shared<ComponentBase>(*component);
    inner_components_.try_emplace(key, component_copy);
  }
  return *this;
}

std::size_t ComponentCollection::Size() const noexcept { return inner_components_.size(); }

bool ComponentCollection::Empty() const noexcept { return inner_components_.empty(); }

void ComponentCollection::Clear() { inner_components_.clear(); }