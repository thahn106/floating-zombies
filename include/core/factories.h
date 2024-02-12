#ifndef CORE_FACTORIES_H
#define CORE_FACTORIES_H

#include <entt/entity/entity.hpp>

#include "utils/types.h"

entt::entity CreatePlayer(entt::registry& registry, PositionType x,
                          PositionType y);
entt::entity CreateEnemy(entt::registry& registry, PositionType x,
                         PositionType y);

#endif  // CORE_FACTORIES_H