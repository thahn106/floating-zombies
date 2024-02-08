#ifndef ENEMY_H
#define ENEMY_H
/*
Enemy.h
Class to handle enemies and their AI brah
Kthxbai
*/
#include "Creature.h"
#include "Player.h"

class Enemy : public Creature {
 public:
  Enemy(int x, int y, int width, int height, int velX, int velY,
        ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture, Player *playa);
  void move();
  void xVelocity();
  void yVelocity();
  void scroll(int x);
  void checkPlatform(int b2_x, int b2_y, int b2_w, int b2_h);
  Player *player;
  void displayName();
  int floorHeight;
  int speed;
  bool jumping;
  bool resetFloorHeight;
  int picCount;
  // private:
};
#endif  // ENEMY_H