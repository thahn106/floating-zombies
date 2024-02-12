#ifndef COMP_PLAYER_ANIMATION_H
#define COMP_PLAYER_ANIMATION_H

#include <entt/entity/registry.hpp>

#include "allegro.h"

#include "core/resource_manager.h"

struct PlayerAnimation {
  ResourceManager* resource_manager;
};

#endif  // COMP_PLAYER_ANIMATION_H