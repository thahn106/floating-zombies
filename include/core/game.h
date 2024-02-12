#ifndef CORE_GAME_H
#define CORE_GAME_H

#include <entt/entity/registry.hpp>

#include "core/resource_manager.h"

class Game {
 public:
  void init();
  bool update();

 private:
  entt::registry registry;

  void SetInitialEnemies(ResourceManager*);
};

#endif  // CORE_GAME_H