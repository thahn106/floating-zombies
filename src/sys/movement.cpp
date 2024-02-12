#include "sys/movement.h"

#include <entt/entity/registry.hpp>

#include "comp/position.h"
#include "comp/physics.h"
#include "utils/types.h"

void update_physics(entt::registry& registry, TimeType delta_time) {
  for (auto entity : registry.view<Position, Physics>()) {
    auto& position = registry.get<Position>(entity);
    auto& physics = registry.get<Physics>(entity);
    position.x += physics.x_velocity * delta_time +
                  0.5 * physics.x_acceleration * delta_time * delta_time;
    position.y += physics.y_velocity * delta_time +
                  0.5 * physics.y_acceleration * delta_time * delta_time;
    physics.x_velocity += physics.x_acceleration * delta_time;
    physics.y_velocity += physics.y_acceleration * delta_time;
  }
}