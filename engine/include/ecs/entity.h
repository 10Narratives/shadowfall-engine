#pragma once

#include <unordered_set>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"
namespace engine::ecs {

/**
 * @class Entity
 * @brief A class representing an entity in a relationship hierarchy.
 *
 * The Entity class allows for the management of parent-child relationships
 * and the associated components of the entity.
 */
class Entity final {
 public:
  /**
   * @brief Default constructor for Entity.
   */
  Entity() = default;

  /**
   * @brief Retrieves the ID of the parent entity.
   * @return The ID of the parent entity.
   */
  [[nodiscard]] EntityID GetParentID() const noexcept;

  /**
   * @brief Remembers a new parent entity by its ID.
   * @param new_parent_id The ID of the new parent entity.
   */
  void RememberParent(const EntityID& new_parent_id);

  /**
   * @brief Checks if this entity is a child of the specified entity.
   * @param entity_id The ID of the potential parent entity.
   * @return True if this entity is a child of the specified entity, otherwise false.
   */
  [[nodiscard]] bool IsChildOf(const EntityID& entity_id) const noexcept;

  /**
   * @brief Retrieves the IDs of all child entities.
   * @return A set of IDs representing the children of this entity.
   */
  [[nodiscard]] std::unordered_set<EntityID, EntityID::Hash> GetChildrenIDs() const noexcept;

  /**
   * @brief Attempts to remember a new child entity by its ID.
   * @param new_child_id The ID of the new child entity.
   * @return True if the child was successfully remembered, otherwise false.
   */
  [[maybe_unused]] bool RememberChild(const EntityID& new_child_id);

  /**
   * @brief Attempts to forget a child entity by its ID.
   * @param target_child_id The ID of the child entity to forget.
   * @return True if the child was successfully forgotten, otherwise false.
   */
  [[maybe_unused]] bool ForgetChild(const EntityID& target_child_id);

  /**
   * @brief Forgets all child entities.
   */
  void ForgetChildren();

  /**
   * @brief Checks if this entity is a parent of the specified child entity.
   * @param target_child_id The ID of the potential child entity.
   * @return True if this entity is a parent of the specified child, otherwise false.
   */
  [[nodiscard]] bool IsParentOf(const EntityID& target_child_id) const noexcept;

  /**
   * @brief Retrieves the components associated with this entity.
   * @return A constant reference to the component collection.
   */
  [[nodiscard]] const ComponentCollection& GetComponents() const noexcept;

  /**
   * @brief Retrieves the components associated with this entity.
   * @return A reference to the component collection.
   */
  [[nodiscard]] ComponentCollection& GetComponents() noexcept;

  /**
   * @brief Sets the components for this entity.
   * @param new_data The new component collection to set.
   */
  void SetComponents(const ComponentCollection& new_data);

  /**
   * @brief Sets the components for this entity using move semantics.
   * @param new_data The new component collection to set, moved.
   */
  void SetComponents(ComponentCollection&& new_data);

  /**
   * @brief Clones the components of this entity.
   * @return A new component collection that is a clone of the original.
   */
  [[nodiscard]] ComponentCollection CloneComponents() const noexcept;

 private:
  EntityID parent_id_{EntityID::GetRootID()};                  ///< ID of the parent entity.
  std::unordered_set<EntityID, EntityID::Hash> children_ids_;  ///< ID of child entities.

  ComponentCollection data_;  ///< Inner components of this entity.
};

}  // namespace engine::ecs