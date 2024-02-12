#include "core/game.h"

#include "entt/entity/registry.hpp"

#include "comp/player_animation.h"
#include "core/factories.h"
#include "core/resource_manager.h"
#include "sys/animate_player.h"
#include "sys/movement.h"
#include "sys/render.h"

void Game::init() {
  // Create player
  entt::entity e = CreatePlayer(registry, 300, 300);
  ResourceManager* player_resource_manager = new ResourceManager(34);
  auto& animation = registry.get<PlayerAnimation>(e);
  SetPlayerResourceManager(player_resource_manager);
  animation.resource_manager = player_resource_manager;
  // SetInitialEnemies();
}

// Called once per frame
// Order of systems is important
bool Game::update() {
  update_physics(registry, 1);
  animate_player(registry);
  render(registry);
  return true;
}

void Game::SetInitialEnemies() {
  // Create enemies
  for (int i = 0; i < 9; i++) {
    CreateEnemy(registry, i * 300, 0);
  }
}