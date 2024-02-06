/*
Bullet.h
This object is a bullet that Creatures make in different ways.
It takes health away from other Creatures
*/

#ifndef _MOVABLE
#define _MOVABLE 1
#include "Movable.h"
#endif

class Bullet : public Movable {
 public:
  Bullet(int x, int y, int x2, int y2, int velX, int velY,
         ALLEGRO_BITMAP *buffer, int dir);
  int direction;  // 1 for left, 2 for right
};

Bullet::Bullet(int x, int y, int x2, int y2, int velX, int velY,
               ALLEGRO_BITMAP *buffer, int dir)
    : Movable(x, y, x2, y2, velX, velY, buffer,
              al_load_bitmap("Unititled.bmp")) {
  direction = dir;
}
