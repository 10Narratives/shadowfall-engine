#pragma once

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "component.h"

namespace engine::ecs {
class ComponentCollection final {
 public:
  ComponentCollection() = default;

  [[nodiscard]] inline bool Empty() const noexcept { return inner_components_.empty(); }

  [[nodiscard]] inline std::size_t Size() const noexcept { return inner_components_.size(); }

  void Clear() { inner_components_.clear(); }

  template <is_component ComponentType>
  [[maybe_unused]] bool Insert(const comp_ptr& new_component);

  template <is_component ComponentType>
  [[maybe_unused]] bool Insert(comp_ptr&& new_component);

  template <is_component ComponentType>
  [[maybe_unused]] bool InsertOrAssign(const comp_ptr& new_component);

  template <is_component ComponentType>
  [[maybe_unused]] bool InsertOrAssign(comp_ptr&& new_component);

  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool Emplace(Args&&... arguments);

  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool TryEmplace(Args&&... arguments);

  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  template <is_component ComponentType>
  [[nodiscard]] comp_ptr Extract();

  template <is_component ComponentType>
  [[nodiscard]] std::shared_ptr<ComponentType> Get() const noexcept;

  template <is_component ComponentType>
  [[nodiscard]] std::shared_ptr<ComponentType> Get() noexcept;

  template <is_component ComponentType>
  [[nodiscard]] bool Has() const noexcept;

  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;

 private:
  std::unordered_map<std::type_index, comp_ptr> inner_components_;
};

template <is_component ComponentType>
[[maybe_unused]] bool ComponentCollection::Insert(const comp_ptr& new_component) {
  comp_ptr new_component_copy{new_component};
  return Insert<ComponentType>(std::move(new_component_copy));
}

template <is_component ComponentType>
[[maybe_unused]] bool ComponentCollection::Insert(comp_ptr&& new_component) {
  return inner_components_.insert({typeid(ComponentType), new_component}).second;
}

template <is_component ComponentType>
[[maybe_unused]] bool ComponentCollection::InsertOrAssign(const comp_ptr& new_component) {
  comp_ptr new_component_copy{new_component};
  return InsertOrAssign<ComponentType>(new_component_copy);
}

template <is_component ComponentType>
[[maybe_unused]] bool ComponentCollection::InsertOrAssign(comp_ptr&& new_component) {
  return inner_components_.insert_or_assign(typeid(ComponentType), new_component).second;
}

template <is_component ComponentType, typename... Args>
[[maybe_unused]] bool ComponentCollection::Emplace(Args&&... arguments) {
  return inner_components_.emplace(typeid(ComponentType), arguments...).second;
}

template <is_component ComponentType, typename... Args>
[[maybe_unused]] bool ComponentCollection::TryEmplace(Args&&... arguments) {
  return inner_components_.try_emplace(typeid(ComponentType), arguments...).second;
}

template <is_component ComponentType>
[[maybe_unused]] bool ComponentCollection::Erase() {
  return inner_components_.erase(typeid(ComponentType)) > 0;
}

template <is_component ComponentType>
[[nodiscard]] comp_ptr ComponentCollection::Extract() {
  auto node_handle = inner_components_.extract(typeid(ComponentType));
  return node_handle.mapped();
}

template <is_component ComponentType>
[[nodiscard]] std::shared_ptr<ComponentType> ComponentCollection::Get() const noexcept {
  std::shared_ptr<ComponentType> total_component{nullptr};
  auto iter = inner_components_.find(typeid(ComponentType));
  if (iter != inner_components_.end()) {
    total_component = std::dynamic_pointer_cast<ComponentType>(iter->second);
  }
  return total_component;
}

template <is_component ComponentType>
[[nodiscard]] std::shared_ptr<ComponentType> ComponentCollection::Get() noexcept {
  std::shared_ptr<ComponentType> total_component{nullptr};
  auto iter = inner_components_.find(typeid(ComponentType));
  if (iter != inner_components_.end()) {
    total_component = std::dynamic_pointer_cast<ComponentType>(iter->second);
  }
  return total_component;
}

template <is_component ComponentType>
[[nodiscard]] bool ComponentCollection::Has() const noexcept {
  return inner_components_.contains(typeid(ComponentType));
}

template <is_component... ComponentTypes>
[[nodiscard]] bool ComponentCollection::HasAll() const noexcept {
  return (inner_components_.contains(typeid(ComponentTypes)) && ...);
}

template <is_component... ComponentTypes>
[[nodiscard]] bool ComponentCollection::HasAny() const noexcept {
  return (inner_components_.contains(typeid(ComponentTypes)) || ...);
}

}  // namespace engine::ecs