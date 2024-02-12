#ifndef CORE_FACTORIES_H
#define CORE_FACTORIES_H

#include <entt/entity/entity.hpp>

#include "core/resource_manager.h"
#include "utils/types.h"

entt::entity CreatePlayer(entt::registry& registry, PositionType x,
                          PositionType y);

bool SetPlayerResourceManager(ResourceManager* player_resource_manager);

entt::entity CreateEnemy(entt::registry& registry, PositionType x,
                         PositionType y);

#endif  // CORE_FACTORIES_H