/*
Creature.h
These objects extend Movable objects. They will be extended by the Player and
the Enemy.
*/

#ifndef MOVABLE
#define MOVABLE 1
#include "Movable.h"
#endif

class Creature : public Movable {
 public:
  Creature(int x, int y, int x2, int y2, int velX, int velY, BITMAP *buffer,
           BITMAP *picture);
  void LoseHealth(int amount);  // Each creature has 100 hit points.
  // void makeBullet(int xLoc, int yLoc, int direction); // Virtual
  void move();  // Virtual
  int health;

 private:
  void destroy();
};

Creature::Creature(int x, int y, int x2, int y2, int velX, int velY,
                   BITMAP *buffer, BITMAP *picture)

    : Movable(x, y, x2, y2, velX, velY, buffer, picture)

{
  health = 150;
}

void Creature::LoseHealth(int amount) {
  health -= amount;
  if (health <= 0) destroy();
}

void Creature::destroy() {}  // ADD WHAT HAPPENS WHEN THEY ARE DESTROYED
