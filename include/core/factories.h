#ifndef CORE_FACTORIES_H
#define CORE_FACTORIES_H

#include <entt/entity/entity.hpp>

#include "utils/types.h"

entt::entity createPlayer(entt::registry& registry, PositionType x,
                          PositionType y);
entt::entity createEnemy(entt::registry& registry, PositionType x,
                         PositionType y);

#endif  // CORE_FACTORIES_H