#include "sys/animate_player.h"

#include <iostream>
#include <entt/entity/registry.hpp>

#include "comp/renderable.h"
#include "comp/player_animation.h"
#include "comp/position.h"

void animate_player(entt::registry& registry) {
  for (auto entity : registry.view<Renderable, PlayerAnimation, Position>()) {
    auto& renderable = registry.get<Renderable>(entity);
    auto& player_animation = registry.get<PlayerAnimation>(entity);
    auto& position = registry.get<Position>(entity);

    renderable.bitmap = player_animation.resource_manager->GetBitmap(1);
    renderable.x = position.x;
    renderable.y = position.y;
  }
}