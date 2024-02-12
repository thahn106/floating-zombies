#include "core/game.h"

#include "entt/entity/registry.hpp"

#include "comp/player_animation.h"
#include "comp/zombie_animation.h"
#include "core/factories.h"
#include "core/resource_manager.h"
#include "sys/animate_player.h"
#include "sys/animate_zombie.h"
#include "sys/movement.h"
#include "sys/render.h"

void Game::init() {
  // Create player
  entt::entity e = CreatePlayer(registry, 300, 300);
  ResourceManager* player_resource_manager = new ResourceManager(34);
  auto& animation = registry.get<PlayerAnimation>(e);
  SetPlayerResourceManager(player_resource_manager);
  animation.resource_manager = player_resource_manager;
  ResourceManager* zombie_resource_manager = new ResourceManager(12);
  SetZombieResourceManager(zombie_resource_manager);
  SetInitialEnemies(zombie_resource_manager);
}

// Called once per frame
// Order of systems is important
bool Game::update() {
  update_physics(registry, 1);
  animate_player(registry);
  AnimateZombie(registry);
  render(registry);
  return true;
}

void Game::SetInitialEnemies(ResourceManager* resource_manager) {
  // Create enemies
  for (int i = 0; i < 9; i++) {
    CreateEnemy(registry, resource_manager, i * 200, 0);
  }
}