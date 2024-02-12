#include "core/factories.h"

#include <entt/entity/registry.hpp>

#include "comp/physics.h"
#include "comp/position.h"
#include "utils/types.h"

entt::entity CreatePlayer(entt::registry& registry, PositionType x,
                          PositionType y) {
  entt::entity e = entt::entity();
  registry.emplace<Position>(e, x, y);
  registry.emplace<Physics>(e, 0, 0, 0, 0);
  return e;
}

entt::entity CreateEnemy(entt::registry& registry, PositionType x,
                         PositionType y) {
  entt::entity e = entt::entity();
  registry.emplace<Position>(e, x, y);
  registry.emplace<Physics>(e, 0, 0, 0, 0);
  return e;
}