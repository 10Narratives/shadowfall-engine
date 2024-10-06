#pragma once

#include <cstddef>
#include <string>
namespace engine::ecs {

/**
 * @brief A class to represent an Entity ID in an ECS (Entity-Component-System) framework.
 *
 * This class is used to uniquely identify entities within an ECS system. It includes functionality to
 * generate new IDs, retrieve the root ID, and compute hashes for the IDs. It also supports comparison
 * operators.
 */
class EntityID final {
 public:
  /**
   * @brief Constructs a new Entity ID.
   *
   * This constructor generates a unique ID based on the current thread ID and the current time in nanoseconds.
   */
  EntityID();

  /**
   * @brief Retrieves the internal string representation of the Entity ID.
   *
   * @return std::string The internal string representation of the Entity ID.
   */
  [[nodiscard]] std::string GetInnerData() const noexcept;

  /**
   * @brief Retrieves the root Entity ID.
   *
   * The root ID is a special ID that represents the root or default Entity ID, typically used as a placeholder.
   *
   * @return EntityID The root Entity ID.
   */
  [[nodiscard]] static EntityID GetRootID() noexcept;

  /**
   * @brief Compares this Entity ID with another for ordering.
   *
   * This operator allows for comparing two Entity IDs for ordering purposes.
   *
   * @param[in] other The other Entity ID to compare with.
   * @return std::strong_ordering The result of the comparison.
   */
  [[nodiscard]] bool operator<=>(const EntityID& other) const = default;

  /**
   * @brief A class to compute the hash value of an Entity ID.
   *
   * This nested struct provides a hash function for Entity ID, suitable for use in hash-based containers.
   */
  struct Hash final {
   public:
    /**
     * @brief Computes the hash value of the given Entity ID.
     *
     * @param[in] id The Entity ID to hash.
     * @return The computed hash value.
     */
    [[nodiscard]] std::size_t operator()(const EntityID& id) const noexcept;
  };

 private:
  std::string inner_data_;  // The internal string representation of the Entity ID.
};

}  // namespace engine::ecs