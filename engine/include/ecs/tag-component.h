#pragma once

#include <concepts>

#include "component-base.h"

namespace engine::ecs {

/**
 * @brief A component used to tag entities in the ECS (Entity Component System).
 *
 * The TagComponent is a lightweight component, inherited from ComponentBase,
 * used to assign tags or markers to entities. It provides default constructors,
 * copy constructors, and assignment operators. It can be used in systems to
 * filter or identify entities based on the presence of specific tags.
 */
struct TagComponent : public ComponentBase {
 public:
  /**
   * @brief Default constructor.
   *
   * Constructs a TagComponent with default settings. This constructor does not
   * perform any specific initialization.
   */
  TagComponent() = default;

  /**
   * @brief Virtual destructor.
   *
   * Ensures proper cleanup of resources when a TagComponent is destroyed.
   */
  ~TagComponent() override = default;

  /**
   * @brief Copy constructor.
   *
   * Initializes a new TagComponent as a copy of another.
   *
   * @param[in] other The TagComponent object to copy.
   */
  TagComponent(const TagComponent& other) = default;

  /**
   * @brief Copy assignment operator.
   *
   * Assigns the values of one TagComponent to another.
   *
   * @param[in] other The TagComponent object to assign from.
   * @return A reference to the assigned TagComponent.
   */
  TagComponent& operator=(const TagComponent& other) = default;
};

/**
 * @brief Concept to check if a type is a valid TagComponent.
 *
 * This concept checks whether a type `T` satisfies the following conditions:
 * - It must satisfy the `is_component` concept.
 * - It must be derived from `TagComponent`.
 *
 * This is used to ensure that a type can be treated as a tag component in the
 * Entity Component System (ECS).
 *
 * @tparam T The type to be checked against the concept requirements.
 */
template <typename T>
concept is_tag_component = is_component<T> && std::derived_from<T, TagComponent>;

}  // namespace engine::ecs