#include "sys/animate_zombie.h"

#include <entt/entity/registry.hpp>

#include "comp/position.h"
#include "comp/renderable.h"
#include "comp/zombie_animation.h"

void AnimateZombie(entt::registry& registry) {
  auto view = registry.view<Renderable, ZombieAnimation, Position>();
  for (auto entity : view) {
    auto& renderable = view.get<Renderable>(entity);
    auto& animation = view.get<ZombieAnimation>(entity);
    auto& position = view.get<Position>(entity);

    animation.current_frame = (animation.current_frame + 1) % 6;
    int direction = animation.direction;
    renderable.bitmap = animation.resource_manager->GetBitmap(
        direction * 6 + animation.current_frame);
    renderable.x = position.x;
    renderable.y = position.y;
  }
}