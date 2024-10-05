#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

namespace engine::ecs {
/**
 * @brief Base structure for all components in the Entity-Component-System (ECS).
 *
 * This structure provides a default constructor and a virtual destructor. All components should derive from this
 * structure.
 */
struct Component {
 public:
  /// Default constructor.
  Component() = default;
  /// Default destructor.
  virtual ~Component() = default;
};

/// Type alias for a shared pointer to a Component.
using comp_ptr = std::shared_ptr<Component>;

/**
 * @brief Concept to check if a type is a valid Component.
 *
 * This concept ensures that the type T is derived from Component and is default constructible.
 *
 * @tparam T Type to be checked
 */
template <typename T>
concept is_component = std::derived_from<T, Component> && std::is_default_constructible_v<T>;

/**
 * @brief Represents a tag component in the Entity-Component System (ECS).
 *
 * This class is derived from Component and serves as a base class for all tag components.
 */
struct TagComponent : public Component {
 public:
  /// Default constructor.
  TagComponent() = default;
  /// Default destructor.
  ~TagComponent() override = default;
};

/**
 * @brief Concept to check if a type is a valid TagComponent.
 *
 * This concept ensures that the type T is derived from TagComponent.
 *
 * @tparam T Type to be checked.
 */
template <typename T>
concept is_tag_component = std::derived_from<T, TagComponent>;

}  // namespace engine::ecs