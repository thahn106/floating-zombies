#ifndef COMP_PHYSICS_H
#define COMP_PHYSICS_H

#include "utils/types.h"

struct Physics {
  PhysicsType x_velocity;
  PhysicsType y_velocity;
  PhysicsType x_acceleration;
  PhysicsType y_acceleration;
};

#endif  // COMP_PHYSICS_H