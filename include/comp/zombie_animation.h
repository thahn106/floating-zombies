#ifndef COMP_ZOMBIE_ANIMATION_H
#define COMP_ZOMBIE_ANIMATION_H

#include "core/resource_manager.h"

struct ZombieAnimation {
  ResourceManager* resource_manager;
  int current_frame;
  int direction;
};

#endif  // COMP_ZOMBIE_ANIMATION_H