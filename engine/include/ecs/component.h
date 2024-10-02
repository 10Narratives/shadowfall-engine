#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

namespace engine::ecs {
struct Component {
 public:
  Component() = default;
  virtual ~Component() = default;
};

using comp_ptr = std::shared_ptr<Component>;

template <typename T>
concept is_component = std::derived_from<T, Component> && std::is_default_constructible_v<T>;

struct TagComponent : public Component {
 public:
  TagComponent() = default;
  ~TagComponent() override = default;
};

template <typename T>
concept is_tag_component = std::derived_from<T, TagComponent>;

}  // namespace engine::ecs