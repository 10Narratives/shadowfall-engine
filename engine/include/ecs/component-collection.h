#pragma once

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "component.h"

namespace engine::ecs {

/**
 * @brief A collection class for managing components.
 *
 * The ComponentCollection class provides mechanisms to store and check for the presence of various component types.
 * It is designed to work with types that satisfy the `is_component` concept. The collection uses `typeid` to handle
 * components of different types and supports efficient checking operations.
 *
 * @note The ComponentCollection class is designed to operate without throwing exceptions, ensuring noexcept guarantees
 * where applicable.
 */
class ComponentCollection final {
 public:
  ComponentCollection() = default;

  [[nodiscard]] inline bool Empty() const noexcept { return inner_components_.empty(); }

  [[nodiscard]] inline std::size_t Size() const noexcept { return inner_components_.size(); }

  void Clear() { inner_components_.clear(); }

  /**
   * @brief Attempts to emplace a new component in the collection.
   *
   * This method tries to emplace a new component of type `ComponentType` in the collection with the provided arguments.
   *
   * @tparam ComponentType Type of the component to be emplaced. Must satisfy the `is_component` concept.
   * @tparam Args Types of arguments for the constructor of `ComponentType`.
   * @param arguments  Arguments to forward to the constructor of `ComponentType`.
   * @return true if the emplacement was successful; otherwise false.
   */
  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool TryEmplace(Args&&... arguments);

  /**
   * @brief Erases a component from the collection.
   *
   * This method attempts to erase a component of type `ComponentType` from the collection.
   *
   * @tparam ComponentType Type of the component to be erased. Must satisfy the `is_component` concept.
   * @return true if the component was successfully erased; otherwise false.
   */
  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  /**
   * @brief Extracts a component from the collection.
   *
   * This method extracts a component of type `ComponentType` from the collection and returns a pointer to it.
   *
   * @tparam ComponentType Type of the component to be extracted. Must satisfy the `is_component` concept.
   * @return A pointer to the extracted component.
   */
  template <is_component ComponentType>
  [[nodiscard]] comp_ptr Extract();

  /**
   * @brief Retrieves a weak pointer to a component from the collection.
   *
   * This method searches for a component of type `ComponentType` in the collection and returns a weak pointer to it.
   *
   * @tparam ComponentType Type of the component to be retrieved. Must satisfy the `is_component` concept.
   * @return A weak pointer to the found component or an empty weak pointer if not found.
   */
  template <is_component ComponentType>
  [[nodiscard]] std::weak_ptr<ComponentType> Get() noexcept;

  /**
   * @brief Checks if the collection contains a component of the specified type.
   *
   * This method determines whether a component of type `ComponentType` exists within the collection.
   *
   * @tparam ComponentType Type of the component to check for. Must satisfy the `is_component` concept.
   * @return true if a component of type `ComponentType` exists in the collection, otherwise false.
   */
  template <is_component ComponentType>
  [[nodiscard]] bool Has() const noexcept;

  /**
   * @brief Checks if the collection contains all the components of the specified types.
   *
   * @tparam ComponentTypes Types of the components to check for. All must satisfy the `is_component` concept.
   * @return true if all components of the types `ComponentTypes` are present in the collection, otherwise false.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  /**
   * @brief Checks if the collection contains any of the components of the specified types.
   *
   * @tparam ComponentTypes ComponentTypes Types of the components to check for. All must satisfy the `is_component`
   * concept.
   * @return true if any component of the types `ComponentTypes` is present in the collection, otherwise false.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;

 private:
  // Inner storage of components, defined internally.
  std::unordered_map<std::type_index, comp_ptr> inner_components_;
};

template <is_component ComponentType, typename... Args>
[[maybe_unused]] bool ComponentCollection::TryEmplace(Args&&... arguments) {
  auto new_component = std::make_unique<ComponentType>(std::forward<Args>(arguments)...);
  return inner_components_.try_emplace(typeid(ComponentType), std::move(new_component)).second;
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
[[nodiscard]] std::weak_ptr<ComponentType> ComponentCollection::Get() noexcept {
  std::shared_ptr<ComponentType> casted_component{nullptr};
  auto found_node = inner_components_.find(typeid(ComponentType));
  if (found_node != inner_components_.end())
    casted_component = std::dynamic_pointer_cast<ComponentType>(found_node->second);
  return casted_component;
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