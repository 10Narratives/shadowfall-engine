#pragma once

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "ecs/component-collection.h"
#include "ecs/entity-id.h"
#include "ecs/entity.h"
namespace engine::ecs {
/**
 * @typedef Predicate
 * @brief A function that takes in a constant ComponentCollection reference and returns a boolean value.
 */
using Predicate = std::function<bool(const ComponentCollection&)>;

/**
 * @class EntityCollection
 * @brief A class that manages collections of Entity objects.
 *
 * The EntityCollection class provides a way to manage collections of Entity objects,
 * allowing for insertion, extraction, and search operations.
 */
class EntityCollection final {
 public:
  /**
   * @brief Default constructor for EntityCollection.
   */
  EntityCollection() = default;

  /**
   * @brief Retrieves the number of entities in the collection.
   * @return The number of entities in the collection.
   */
  [[nodiscard]] std::size_t Size() const noexcept;

  /**
   * @brief Checks if the collection is empty.
   * @return True if the collection is empty, otherwise false.
   */
  [[nodiscard]] bool Empty() const noexcept;

  /**
   * @brief Clears the collection by removing all entities.
   */
  void Clear();

  /**
   * @brief Inserts a new entity into the collection.
   * @param entity_data The data associated with the new entity.
   * @param parent_id The ID of the parent entity to associate the new entity with.
   * @return An ID-value pair indicating whether the insertion was successful and the ID of the new entity.
   */
  [[nodiscard]] std::pair<EntityID, bool> Insert(const ComponentCollection& entity_data,
                                                 const EntityID& parent_id = EntityID::GetRootID());

  /**
   * @brief Inserts a new entity into the collection, using move semantics.
   * @param entity_data The data associated with the new entity, moved.
   * @param parent_id The ID of the parent entity to associate the new entity with.
   * @return An ID-value pair indicating whether the insertion was successful and the ID of the new entity.
   */
  [[nodiscard]] std::pair<EntityID, bool> Insert(ComponentCollection&& entity_data,
                                                 const EntityID& parent_id = EntityID::GetRootID());

  /**
   * @brief Extracts the ComponentCollection associated with the specified entity ID.
   * @param target_id The ID of the entity to extract.
   * @return An ID-value pair indicating whether the extraction was successful and the associated ComponentCollection.
   */
  [[nodiscard]] std::pair<ComponentCollection, bool> Extract(const EntityID& target_id);

  /**
   * @brief Erases the entity associated with the specified entity ID.
   * @param entity_id The ID of the entity to erase.
   * @return True if the entity was successfully erased, otherwise false.
   */
  [[maybe_unused]] bool Erase(const EntityID&);

  /**
   * @brief Erases all entities that meet a certain predicate.
   * @param predicate The predicate function that entities must meet to be erased.
   * @return True if entities were successfully erased, otherwise false.
   */
  [[maybe_unused]] bool EraseIf(const Predicate& predicate);

  /**
   * @brief Retrieves the ComponentCollection associated with the specified entity ID.
   * @param entity_id The ID of the entity to retrieve.
   * @return A mutable reference to the associated ComponentCollection.
   */
  [[nodiscard]] ComponentCollection& At(const EntityID& entity_id);

  /**
   * @brief Retrieves the ComponentCollection associated with the specified entity ID.
   * @param entity_id The ID of the entity to retrieve.
   * @return A constant reference to the associated ComponentCollection.
   */
  [[nodiscard]] const ComponentCollection& At(const EntityID& entity_id) const;

  /**
   * @brief Counts the number of entities that meet a certain predicate.
   * @param predicate The predicate function that entities must meet to be counted.
   * @return The number of entities that meet the predicate.
   */
  [[nodiscard]] std::size_t CountIf(const Predicate& predicate);

  /**
   * @brief Retrieves a vector of all entity IDs that meet a certain predicate.
   * @param predicate The predicate function that entity IDs must meet to be included.
   * @return A vector containing all entity IDs that meet the predicate.
   */
  [[nodiscard]] std::vector<EntityID> Filter(const Predicate& predicate) const noexcept;

  /**
   * @brief Checks if the entity with the specified entity ID exists in the collection.
   * @param entity_id The ID of the entity to search for.
   * @return True if the entity is in the collection, otherwise false.
   */
  [[nodiscard]] bool Contains(const EntityID& entity_id) const noexcept;

 private:
  std::unordered_map<EntityID, Entity, EntityID::Hash> inner_entities_;  ///< The map of entity IDs to entities.
};
}  // namespace engine::ecs