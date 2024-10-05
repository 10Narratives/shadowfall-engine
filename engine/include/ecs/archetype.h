#pragma once

#include "component-collection.h"
#include "component.h"
namespace engine::ecs {

/**
 * @class Archetype
 * @brief A template class to define and manage archetypes consisting of multiple components.
 *
 * The Archetype class template helps in organizing and managing groups of components, ensuring that
 * collections can be easily checked for required components, instantiated with all the required components,
 * or supplemented with missing components.
 *
 * @tparam RequiredComponentTypes Types of components that make up the archetype. Must satisfy the `is_component`
 * concept.
 */
template <is_component... RequiredComponentTypes>
class Archetype final {
 public:
  /// Default constructor for Archetype.
  Archetype() = default;

  /**
   * @brief Checks if all required components of the archetype are present in the given collection.
   *
   * @param[in] collection The ComponentCollection to check.
   * @return true if all required components are present in the collection, otherwise false.
   */
  [[nodiscard]] static bool IsPresentedIn(const ComponentCollection& collection) noexcept;

  /**
   * @brief Creates and returns a new ComponentCollection instance containing all required components of the archetype.
   *
   * @return A new ComponentCollection instance with all required components.
   */
  [[nodiscard]] static ComponentCollection CreateInstance() noexcept;

  /**
   * \brief Supplements the given collection with any missing required components of the archetype.
   *
   * \param[in] collection The ComponentCollection to supplement.
   * \return `true` if at least one component was successfully added, otherwise `false`.
   */
  [[maybe_unused]] static bool Supplement(ComponentCollection& collection) noexcept;
};

template <is_component... RequiredComponentTypes>
bool Archetype<RequiredComponentTypes...>::IsPresentedIn(const ComponentCollection& collection) noexcept {
  return collection.HasAll<RequiredComponentTypes...>();
}

template <is_component... RequiredComponentTypes>
ComponentCollection Archetype<RequiredComponentTypes...>::CreateInstance() noexcept {
  ComponentCollection new_collection;
  (new_collection.TryEmplace<RequiredComponentTypes>(), ...);
  return new_collection;
}

template <is_component... RequiredComponentTypes>
bool Archetype<RequiredComponentTypes...>::Supplement(ComponentCollection& collection) noexcept {
  return (collection.TryEmplace<RequiredComponentTypes>() || ...);
}
}  // namespace engine::ecs