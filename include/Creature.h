#ifndef CREATURE_H
#define CREATURE_H
/*
Creature.h
These objects extend Movable objects. They will be extended by the Player and
the Enemy.
*/
#include "Movable.h"
#include "allegro.h"
class Creature : public Movable {
 public:
  Creature(int x, int y, int x2, int y2, int velX, int velY,
           ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture);
  void LoseHealth(int amount);  // Each creature has 100 hit points.
  // void makeBullet(int xLoc, int yLoc, int direction); // Virtual
  void move();  // Virtual
  int health;

 private:
  void destroy();
};

#endif  // CREATURE_H