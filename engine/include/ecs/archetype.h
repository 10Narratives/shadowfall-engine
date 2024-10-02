#pragma once

#include "component-collection.h"
#include "component.h"
namespace engine::ecs {
template <is_component... RequiredComponentTypes>
class Archetype final {
 public:
  Archetype() = default;

  // Checks if `collection` complies to this archetype
  [[nodiscard]] static bool IsPresentedIn(const ComponentCollection& collection) noexcept;

  // Creates instance of collection where all required components are presented
  [[nodiscard]] static ComponentCollection CreateInstance() noexcept;

  // Supplement gotten collection to a set of required components
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