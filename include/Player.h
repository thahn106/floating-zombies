#ifndef PLAYER_H
#define PLAYER_H
/*
Player.h
This class is the player that moves using the arrow keys.
The player will have a bit of intertia when it moves and it will use a quadratic
to jump.
*/
#include "Creature.h"
#include "allegro.h"
class Player : public Creature {
 public:
  Player(int x, int y, int x2, int y2, int velX, int velY,
         ALLEGRO_BITMAP *buffer, bool *key);
  void move();
  void xvelocity();
  void yvelocity();
  void hit();
  void checkPlatform(int, int, int, int);
  void makeBullet(int xLoc, int yLoc, int direction);
  bool *key;
  int maxxVel;  // DO NOT CHANGE
  int picCount;
  int jumpCount;
  int walkCount;
  int idleCount;
  int idleRest;
  int slow;
  int slowWalk;
  int floorHeight;
  bool resetFloorHeight;

 private:
  ALLEGRO_BITMAP *pics[34];
};
#endif  // PLAYER_H