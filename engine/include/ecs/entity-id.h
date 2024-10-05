#pragma once

#include <cstddef>
#include <string>
namespace engine::ecs {

/**
 * @class EntityID
 * @brief A class to represent a unique identifier for entities.
 *
 * The EntityID class encapsulates a string representation of an ID and provides methods
 * to retrieve its data, perform comparisons, and manage hash computations.
 */
class EntityID final {
 public:
  /**
   * @brief Default constructor for EntityID.
   *
   * Constructs an EntityID by combining the current thread ID and the current time
   * in nanoseconds since the epoch.
   */
  EntityID();

  /**
   * @brief Retrieves the inner data of the EntityID.
   *
   * @return String representation of the inner data.
   */
  [[nodiscard]] std::string GetInnerData() const noexcept;

  /**
   * \brief Retrieves the root EntityID.
   *
   * \return The root EntityID instance with cleared inner data.
   */
  static EntityID GetRootID() noexcept;

  /**
   * @brief Comparison operator for EntityID.
   *
   * Allows comparisons of EntityID instances using the spaceship operator (<=>
   *
   * @param entity_id The EntityID to compare against.
   * @return The result of the comparison.
   */
  [[nodiscard]] bool operator<=>(const EntityID& entity_id) const = default;

  /**
   * @struct Hash
   * @brief A hash function for EntityID.
   *
   * This struct provides a method to compute a hash value for an EntityID.
   */
  struct Hash final {
   public:
    /**
     * @brief Computes the hash value for a given EntityID.
     *
     * Utilizes std::hash for the inner string data.
     *
     * @param[in] id The EntityID to hash.
     * @return The computed hash value as a std::size_t.
     */
    [[nodiscard]] std::size_t operator()(const EntityID& id) const noexcept;
  };

 private:
  std::string inner_data_;  // Inner data representation of the EntityID.
};

}  // namespace engine::ecs