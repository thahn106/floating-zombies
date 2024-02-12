#include "sys/move_zombie.h"

#include <entt/entity/registry.hpp>

#include "comp/player.h"
#include "comp/position.h"
#include "comp/physics.h"
#include "comp/zombie_ai.h"
#include "comp/zombie_animation.h"
#include "utils/types.h"

void MoveZombies(entt::registry& registry) {
  auto player_view = registry.view<Player, Position>();
  PositionType player_x;
  PositionType player_y;
  for (auto entity : player_view) {
    auto& position = player_view.get<Position>(entity);
    player_x = position.x;
    player_y = position.y;
  }

  auto view = registry.view<ZombieAI, Position, Physics, ZombieAnimation>();
  for (auto entity : view) {
    auto& position = view.get<Position>(entity);
    auto& physics = view.get<Physics>(entity);
    auto& animation = view.get<ZombieAnimation>(entity);

    // TODO: make this part of the zombie AI component
    PhysicsType zombieSpeed = 10;

    if (position.x < player_x) {
      physics.x_velocity = zombieSpeed;
      animation.direction = 1;
    } else {
      physics.x_velocity = -zombieSpeed;
      animation.direction = 0;
    }
  }
}