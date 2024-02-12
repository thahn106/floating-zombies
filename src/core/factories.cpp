#include "core/factories.h"

#include <entt/entity/registry.hpp>

#include "allegro.h"

#include "comp/physics.h"
#include "comp/position.h"
#include "comp/renderable.h"
#include "core/resource_manager.h"
#include "comp/player_animation.h"
#include "utils/types.h"

entt::entity CreatePlayer(entt::registry& registry, PositionType x,
                          PositionType y) {
  entt::entity e = registry.create();
  registry.emplace<Position>(e, x, y);
  registry.emplace<Physics>(e, 0, 0, 0, 0);
  registry.emplace<Renderable>(e, (ALLEGRO_BITMAP*)NULL, 0, 0);
  registry.emplace<PlayerAnimation>(e, (ResourceManager*)NULL);
  return e;
}

bool SetPlayerResourceManager(ResourceManager* player_resource_manager) {
  player_resource_manager->LoadBitmapWithAlpha("crouch1.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch2.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch3.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch4.bmp");
  player_resource_manager->LoadBitmapWithAlpha("idle1.bmp");
  player_resource_manager->LoadBitmapWithAlpha("idle2.bmp");
  player_resource_manager->LoadBitmapWithAlpha("idle3.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump1.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump2.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump3.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump4.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run6.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run5.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run4.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run3.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run2.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run1.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch1b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch2b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch3b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("crouch4b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("idle1b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("idle2b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("idle3b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump1b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump2b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump3b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("jump4b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run6b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run5b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run4b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run3b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run2b.bmp");
  player_resource_manager->LoadBitmapWithAlpha("run1b.bmp");
  return true;
}

entt::entity CreateEnemy(entt::registry& registry, PositionType x,
                         PositionType y) {
  entt::entity e = registry.create();
  registry.emplace<Position>(e, x, y);
  registry.emplace<Physics>(e, 0, 0, 0, 0);
  registry.emplace<Renderable>(e, (ALLEGRO_BITMAP*)NULL, 0, 0);
  return e;
}