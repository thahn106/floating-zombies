/*
Movable.h
These objects are objects that will move in some sort of way in the game.
Extended by Creatures and Bullets.
*/
#ifndef ALLEGRO
#define ALLEGRO 1
#include <allegro.h>
#endif
class Movable {
 public:
  Movable(int x, int y, int width, int height, int velX, int velY,
          BITMAP *buffer, BITMAP *picture);
  Movable(int x, int y, int width, int height, int velX, int velY,
          BITMAP *buffer, BITMAP *picture, int dir);
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
  BITMAP *pic;
  BITMAP *buf;
};

Movable::Movable(int x, int y, int width, int height, int velX, int velY,
                 BITMAP *buffer, BITMAP *picture) {
  locationX = x;
  locationY = y;
  wid = width;
  hgt = height;
  xVel = velX;
  yVel = velY;
  pic = picture;
  buf = buffer;
  jumping = true;
  direction = 2;
}

Movable::Movable(int x, int y, int width, int height, int velX, int velY,
                 BITMAP *buffer, BITMAP *picture, int dir) {
  locationX = x;
  locationY = y;
  wid = width;
  hgt = height;
  xVel = velX;
  yVel = velY;
  pic = picture;
  buf = buffer;
  jumping = true;
  direction = dir;
}

/*
Displays the object on the screen.
*/
void Movable::display() { draw_sprite(buf, pic, locationX, locationY); }

/*
Moves the object on the screen.
*/
void Movable::move(int x, int y) {
  locationX += x;
  locationY += y;
}

void Movable::setLocX(int x) { locationX = x; }

void Movable::setLocY(int y) { locationY = y; }

void Movable::changeLocX(int x) { locationX += x; }

void Movable::changeLocY(int y) { locationY += y; }

int Movable::checkCollision(int x, int y, int w, int h) {
  if (x > locationX + wid) return 0;  // false
  if (x + w < locationX) return 0;
  if (y > locationY + hgt) return 0;
  if (y + h < locationY) return 0;
  return 1;
}

void Movable::drawHitBox() {
  rect(buf, locationX, locationY, locationX + wid, locationY + hgt,
       makecol(0, 0, 0));
}
