#ifndef MOVABLE_H
#define MOVABLE_H
/*
Movable.h
These objects are objects that will move in some sort of way in the game.
Extended by Creatures and Bullets.
*/
#include "allegro.h"
class Movable {
 public:
  Movable(int x, int y, int width, int height, int velX, int velY,
          ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture);
  Movable(int x, int y, int width, int height, int velX, int velY,
          ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture, int dir);
  void move(int x, int y);  // Virtual
  void setLocX(int x);
  void changeLocX(int x);
  void setLocY(int y);
  void changeLocY(int y);
  void destroy();
  void checkIfHit();
  void display();
  void drawHitBox();
  int checkCollision(int b2_x, int b2_y, int b2_w, int b2_h);
  // Below are public FOR NOW. Later add getters and setters.
  bool jumping;
  int locationX;  // Top left point of the creature.
  int locationY;
  int wid;
  int hgt;
  int xVel;
  int yVel;
  int direction;
  ALLEGRO_BITMAP *pic;
  ALLEGRO_BITMAP *buf;
};
#endif  // MOVABLE_H