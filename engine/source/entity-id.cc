#include "ecs/entity-id.h"

#include <chrono>
#include <functional>
#include <thread>
using engine::ecs::EntityID;

EntityID::EntityID() {
  thread_id_ = std::this_thread::get_id();
  time_point_ = ecs_clock::now();
}

std::thread::id EntityID::GetThreadID() const noexcept { return thread_id_; }

engine::ecs::ecs_time_point EntityID::GetTimePoint() const noexcept { return time_point_; }

std::size_t EntityID::Hash::operator()(const EntityID& id) const noexcept {
  auto duration = id.time_point_.time_since_epoch();
  auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  return std::hash<std::int64_t>{}(nanoseconds) ^ std::hash<std::thread::id>{}(id.thread_id_);
}

EntityID EntityID::GetRootID() noexcept {
  EntityID root_id;
  root_id.thread_id_ = std::thread::id{};
  root_id.time_point_ = ecs_clock::from_time_t(0);
  return root_id;
}