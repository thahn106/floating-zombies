#include "Creature.h"
#include "allegro.h"
Creature::Creature(int x, int y, int x2, int y2, int velX, int velY,
                   ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture)
    : Movable(x, y, x2, y2, velX, velY, buffer, picture) {
  health = 150;
}

void Creature::LoseHealth(int amount) {
  health -= amount;
  if (health <= 0) destroy();
}

void Creature::destroy() {}  // ADD WHAT HAPPENS WHEN THEY ARE DESTROYED