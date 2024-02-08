#ifndef IMMOVABLE_H
#define IMMOVABLE_H
/*
    Immovable.h
    Header file for all immovable and static objects.
*/
#include "allegro.h"

class Immovable {
 public:
  Immovable(int xPos, int yPos, int xPos1, int yPos1, ALLEGRO_BITMAP *picture,
            ALLEGRO_BITMAP *buffer);
  void display();
  void drawHitBox();
  void move(int x);
  int checkCollision(int, int, int, int);
  int locationX;
  int locationY;
  int wid;
  int hgt;

 private:
  ALLEGRO_BITMAP *pic;
  ALLEGRO_BITMAP *buf;
};
#endif  // IMMOVABLE_H