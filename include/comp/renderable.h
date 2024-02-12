#ifndef COMP_RENDERABLE_H
#define COMP_RENDERABLE_H

#include "allegro.h"
#include "utils/types.h"

struct Renderable {
  ALLEGRO_BITMAP *bitmap;
  ScreenCoordType x;
  ScreenCoordType y;
};

#endif  // COMP_RENDERABLE_H