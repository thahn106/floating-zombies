#include "core/game.h"

#include "core/factories.h"
#include "sys/movement.h"
#include "sys/render.h"

void Game::init() {
  // Create player
  CreatePlayer(registry, 300, 300);
  SetInitialEnemies();
}

// Called once per frame
// Order of systems is important
bool Game::update() {
  update_physics(registry, 1);
  render(registry);
}

void Game::SetInitialEnemies() {
  // Create enemies
  for (int i = 0; i < 9; i++) {
    CreateEnemy(registry, i * 300, 0);
  }
}