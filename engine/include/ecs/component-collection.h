#pragma once

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "component-base.h"

namespace engine::ecs {

/**
 * @defgroup ComponentCollectionGroup ComponentCollection
 * @brief A class for managing components in an Entity Component System (ECS).
 *
 * This class provides functionality for managing, adding, removing, and querying components
 * based on their type. It uses type erasure via std::shared_ptr to allow components of various
 * types to be stored in a single container.
 * @{
 */

/**
 * @brief ComponentCollection class manages components in an ECS.
 *
 * This class handles components in a type-safe way, allowing for adding, removing,
 * and querying components at runtime. Components are stored using a type-based key
 * (std::type_index) and shared ownership is ensured through std::shared_ptr.
 */
class ComponentCollection final {
 public:
  /**
   * @name Constructors
   * @{
   */

  /**
   * @brief Default constructor.
   *
   * Creates an empty ComponentCollection.
   */
  ComponentCollection() = default;

  /**
   * @brief Copy constructor.
   *
   * Performs a deep copy of all components in the collection.
   *
   * @param other The collection to copy from.
   */
  ComponentCollection(const ComponentCollection& other);

  /**
   * @brief Copy assignment operator.
   *
   * Performs a deep copy of all components from the specified collection.
   *
   * @param other The collection to copy from.
   * @return A reference to the current instance.
   */
  ComponentCollection& operator=(const ComponentCollection& other);
  /** @} */  // end of Constructors

  /**
   * @name ComponentCollection State Methods
   * @{
   */

  /**
   * @brief Get the number of components in the collection.
   *
   * @return The number of components in the collection.
   */
  [[nodiscard]] std::size_t Size() const noexcept;

  /**
   * @brief Check if the collection is empty.
   *
   * @return true if the collection contains no components, false otherwise.
   */
  [[nodiscard]] bool Empty() const noexcept;

  /**
   * @brief Clears all components from the collection.
   */
  void Clear();

  /** @} */  // end of ComponentCollection State Methods

  /**
   * @brief Emplace a new component of type ComponentType into the collection.
   *
   * This method constructs a new component of the given type using the supplied arguments
   * and adds it to the collection. If a component of this type already exists, it is not replaced.
   *
   * @tparam ComponentType The type of the component to be added.
   * @tparam Args Types of the arguments to pass to the component's constructor.
   * @param arguments The arguments forwarded to the constructor.
   * @return true if the component was successfully emplaced, false if it already exists.
   */
  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool Emplace(Args&&... arguments);

  /**
   * @brief Remove a component of the specified type from the collection.
   *
   * Removes the component from the collection if it exists.
   *
   * @tparam ComponentType The type of the component to be removed.
   * @return true if the component was successfully removed, false otherwise.
   */
  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  /**
   * @brief Extract and remove a component of the specified type.
   *
   * Removes the component from the collection and returns it as a shared pointer.
   *
   * @tparam ComponentType The type of the component to extract.
   * @return A shared pointer to the extracted component, or nullptr if it does not exist.
   */
  template <is_component ComponentType>
  [[nodiscard]] std::shared_ptr<ComponentBase> Extract();

  /**
   * @brief Get a weak reference to a component of the specified type.
   *
   * Returns a weak pointer to the component if it exists in the collection.
   *
   * @tparam ComponentType The type of the component to get.
   * @return A weak pointer to the requested component, or an expired weak pointer if the component is not found.
   */
  template <is_component ComponentType>
  [[nodiscard]] std::weak_ptr<ComponentType> Get() const noexcept;

  /** @} */  // end of Component Manipulation Methods

  /**
   * @name Component Query Methods
   * @{
   */

  /**
   * @brief Check if all specified component types are present in the collection.
   *
   * Verifies that the collection contains components of all the specified types.
   *
   * @tparam ComponentTypes The types of components to check.
   * @return true if all components are present, false otherwise.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  /**
   * @brief Check if any of the specified component types are present in the collection.
   *
   * Verifies if at least one component of the specified types exists in the collection.
   *
   * @tparam ComponentTypes The types of components to check.
   * @return true if any of the components are present, false otherwise.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;

  /**
   * @brief Check if none of the specified tag component types are present in the collection.
   *
   * Verifies that none of the components of the specified types are present.
   *
   * @tparam ComponentTypes The types of tag components to check.
   * @return true if none of the specified tag components are present, false otherwise.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasNoneOf() const noexcept;

  /** @} */  // end of Component Query Methods

 private:
  // Internal storage for components.
  std::unordered_map<std::type_index, std::shared_ptr<ComponentBase>> inner_components_;
};

template <is_component ComponentType, typename... Args>
bool ComponentCollection::Emplace(Args&&... arguments) {
  auto new_component = std::make_shared<ComponentType>(std::forward<Args>(arguments)...);
  return inner_components_.try_emplace(typeid(ComponentType), std::move(new_component)).second;
}

template <is_component ComponentType>
bool ComponentCollection::Erase() {
  return inner_components_.erase(typeid(ComponentType)) > 0;
}

template <is_component ComponentType>
std::shared_ptr<ComponentBase> ComponentCollection::Extract() {
  std::shared_ptr<ComponentBase> extracted_component{nullptr};
  if (inner_components_.contains(typeid(ComponentType))) {
    auto node = inner_components_.extract(typeid(ComponentType));
    extracted_component = std::move(node.mapped());
  }
  return extracted_component;
}

template <is_component ComponentType>
std::weak_ptr<ComponentType> ComponentCollection::Get() const noexcept {
  std::shared_ptr<ComponentType> found_component{nullptr};
  auto iter = inner_components_.find(typeid(ComponentType));
  if (iter != inner_components_.end()) {
    found_component = iter->second;
  }
  return found_component;
}

template <is_component... ComponentTypes>
bool ComponentCollection::HasAll() const noexcept {
  return (inner_components_.contains(typeid(ComponentTypes)) && ...);
}

template <is_component... ComponentTypes>
bool ComponentCollection::HasAny() const noexcept {
  return (inner_components_.contains(typeid(ComponentTypes)) || ...);
}

template <is_component... ComponentTypes>
bool ComponentCollection::HasNoneOf() const noexcept {
  return !HasAll<ComponentTypes...>();
}

}  // namespace engine::ecs