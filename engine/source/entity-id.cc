#include "ecs/entity-id.h"

#include <chrono>
#include <cstddef>
#include <functional>
#include <sstream>
#include <thread>
using engine::ecs::EntityID;

EntityID::EntityID() {
  std::stringstream stream;
  stream << std::this_thread::get_id();
  stream << ".";

  auto now = std::chrono::high_resolution_clock::now();
  auto duration = now.time_since_epoch();
  stream << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

  inner_data_ = stream.str();
}

EntityID EntityID::GetRootID() noexcept {
  EntityID root_id;
  root_id.inner_data_.clear();
  return root_id;
}

std::size_t EntityID::Hash::operator()(const EntityID& id) const noexcept {
  return std::hash<std::string>{}(id.inner_data_);
}