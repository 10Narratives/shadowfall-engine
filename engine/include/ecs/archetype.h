#pragma once

#include "ecs/component-base.h"
#include "ecs/component-collection.h"
namespace engine::ecs {

/**
 * @brief A class that represents an Archetype within an Entity-Component-System (ECS).
 *
 * This class template is used to manage and ensure the presence of a specific set of component types
 * within a component collection in an ECS system. It provides functionality to check for required components,
 * create new instances of component collections, and supplement existing collections with missing components.
 *
 * @tparam RequiredComponentTypes Variadic template parameters representing the component types required by this
 * Archetype.
 */
template <is_component... RequiredComponentTypes>
class Archetype final {
 public:
  /**
   * @brief Checks if all the required component types are present in the given component collection.
   *
   * This function inspects the provided component collection and verifies whether it contains all the component types
   * required by this Archetype.
   *
   * @param[in] collection The component collection to check against.
   * @return true If all required component types are present in the collection, false otherwise.
   */
  [[nodiscard]] static bool IsPresentedIn(const ComponentCollection& collection) noexcept;

  /**
   * @brief Creates a new component collection instance containing all the required component types.
   *
   * This function constructs a new instance of a component collection and populates it with all the component types
   * specified by this Archetype.
   *
   * @return A new component collection containing all the required component types.
   */
  [[nodiscard]] static ComponentCollection CreateInstance();

  /**
   * @brief Ensures the given component collection contains all the required component types.
   *
   * This function supplements the provided component collection by adding any missing component types that are required
   * by this Archetype. If all required component types are already present, no changes are made.
   *
   * @param[in] collection The component collection to supplement.
   * @return true If all required component types are successfully added to the collection, false otherwise.
   */
  [[maybe_unused]] static bool Supplement(ComponentCollection& collection);
};

template <is_component... RequiredComponentTypes>
bool Archetype<RequiredComponentTypes...>::IsPresentedIn(const ComponentCollection& collection) noexcept {
  return collection.HasAll<RequiredComponentTypes...>();
}

template <is_component... RequiredComponentTypes>
ComponentCollection Archetype<RequiredComponentTypes...>::CreateInstance() {
  ComponentCollection new_instance;
  (new_instance.Emplace<RequiredComponentTypes>(), ...);
  return new_instance;
}

template <is_component... RequiredComponentTypes>
bool Archetype<RequiredComponentTypes...>::Supplement(ComponentCollection& collection) {
  return (collection.Emplace<RequiredComponentTypes>() && ...);
}

}  // namespace engine::ecs