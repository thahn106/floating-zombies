#include "core/game.h"

#include "sys/movement.h"
#include "sys/render.h"

void Game::init() {}

// Called once per frame
// Order of systems is important
bool Game::update() {
  update_physics(registry, 1);
  render(registry);
}