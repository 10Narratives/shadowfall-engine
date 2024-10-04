#pragma once

#include <cstddef>
#include <string>
namespace engine::ecs {

class EntityID final {
 public:
  EntityID();  // Constructor

  // Retrieves inner data of EntityID
  [[nodiscard]] std::string GetInnerData() const noexcept;

  // Retrieves root id
  static EntityID GetRootID() noexcept;

  [[nodiscard]] bool operator<=>(const EntityID& entity_id) const = default;

  struct Hash final {
   public:
    [[nodiscard]] std::size_t operator()(const EntityID& id) const noexcept;
  };

 private:
  std::string inner_data_;
};

}  // namespace engine::ecs