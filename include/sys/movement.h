#ifndef SYS_MOVEMENT_H
#define SYS_MOVEMENT_H

#include <entt/entity/registry.hpp>

#include "comp/physics.h"
#include "comp/position.h"
#include "utils/types.h"

void update_physics(entt::registry& registry, TimeType delta_time);

#endif  // SYS_MOVEMENT_H