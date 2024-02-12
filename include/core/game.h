#ifndef CORE_GAME_H
#define CORE_GAME_H

#include <entt/entity/registry.hpp>

class Game {
 public:
  void init();
  bool update();

 private:
  entt::registry registry;

  void SetInitialEnemies();
};

#endif  // CORE_GAME_H