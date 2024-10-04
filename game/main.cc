#include <exception>
#include <ios>
#include <iostream>
#include <sstream>

#include "ecs/component.h"
using engine::ecs::Component;

struct Position final : public Component {
 public:
  Position() = default;
  Position(float x, float y) : x_coord(x), y_coord(y) {}

  float x_coord{}, y_coord{};
};

struct Velocity final : public Component {
 public:
  Velocity() = default;
  Velocity(float x_comp, float y_comp) : d_x(x_comp), d_y(y_comp) {}

  float d_x{}, d_y{};
};

#include "ecs/component-collection.h"
using engine::ecs::ComponentCollection;

#include "ecs/archetype.h"
using engine::ecs::Archetype;

using Placeable = Archetype<Position, Velocity>;

#include "ecs/entity-id.h"
using engine::ecs::EntityID;

int main() {
  try {
    ComponentCollection collection;
    collection.TryEmplace<Position>(10, 12);
    auto position = collection.Get<Position>();
    if (auto tmp = position.lock()) {
      std::cout << "Position: {" << tmp->x_coord << ", " << tmp->y_coord << "}\n";
    }
    std::cout << std::boolalpha << collection.Has<Position>() << "\n";

    std::cout << std::boolalpha << Placeable::IsPresentedIn(collection) << "\n";
    Placeable::Supplement(collection);
    std::cout << std::boolalpha << Placeable::IsPresentedIn(collection) << "\n";

    auto placeable_collection = Placeable::CreateInstance();
    std::cout << std::boolalpha << Placeable::IsPresentedIn(placeable_collection) << "\n";

    auto id = EntityID::GetRootID();
    std::cout << id.GetThreadID() << " " << id.GetTimePoint() << "\n";

    EntityID i1{};
    EntityID i2{};
    std::cout << i1.GetThreadID() << " " << i1.GetTimePoint() << "\n";
    std::cout << i2.GetThreadID() << " " << i2.GetTimePoint() << "\n";

    std::ostringstream out;
    std::hex(out);
    out << i1.GetThreadID();
    std::cout << "Hex " << out.str() << "\n";

  } catch (const std::exception& err) {
    std::cout << err.what() << "\n";
    return -1;
  }
  return 0;
}