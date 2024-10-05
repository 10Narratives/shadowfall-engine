#pragma once

#include <concepts>
#include <type_traits>
namespace engine::ecs {

/**
 * @brief Base strucure for components in a entity-component-system (ECS).
 *
 * This strucure provides a base structure for all components. It includes
 * default constructors, destructors, and assignment operators.
 */
struct ComponentBase {
 public:
  /**
   * @brief Default constructor.
   *
   * Constructs a ComponentBase object. This is a default, no-op constructor.
   */
  ComponentBase() = default;

  /**
   * @brief Virtual destructor.
   *
   * Ensures that derived classes will have their destructors called correctly.
   */
  virtual ~ComponentBase() = default;

  /**
   * @brief Copy constructor.
   *
   * Initializes a new ComponentBase object as a copy of another.
   *
   * @param other The ComponentBase object to copy.
   */
  ComponentBase(const ComponentBase& other) = default;

  /**
   * @brief Copy assignment operator.
   *
   * Assigns the values of one ComponentBase object to another.
   *
   * @param[in] other The ComponentBase object to assign from.
   * @return A reference to the assigned ComponentBase object.
   */
  ComponentBase& operator=(const ComponentBase& other) = default;
};

/**
 * @brief Concept to check if a type is a valid component.
 *
 * This concept checks whether a type `T` satisfies the following conditions:
 * - It must be derived from `ComponentBase`.
 * - It must be default constructible.
 * - It must be copy constructible.
 * - It must be copy assignable.
 *
 * @tparam T The type to be checked against the concept requirements.
 */
template <typename T>
concept is_component = std::derived_from<T, ComponentBase> && std::is_default_constructible_v<T> &&
                       std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;

}  // namespace engine::ecs