#pragma once

#include <chrono>
#include <thread>
namespace engine::ecs {

using ecs_clock = std::chrono::high_resolution_clock;
using ecs_time_point = std::chrono::time_point<ecs_clock>;

class EntityID final {
 public:
  EntityID();

  [[nodiscard]] inline std::thread::id GetThreadID() const noexcept;

  [[nodiscard]] inline ecs_time_point GetTimePoint() const noexcept;

  [[nodiscard]] inline bool operator<=>(const EntityID& other) const noexcept = default;

  struct Hash {
   public:
    [[nodiscard]] std::size_t operator()(const EntityID& id) const noexcept;
  };

  [[nodiscard]] static EntityID GetRootID() noexcept;

 private:
  std::thread::id thread_id_;
  ecs_time_point time_point_;
};

}  // namespace engine::ecs