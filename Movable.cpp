#include "Movable.h"
#include "allegro.h"

Movable::Movable(int x, int y, int width, int height, int velX, int velY,
                 ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture) {
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
                 ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture, int dir) {
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
void Movable::display() { al_draw_bitmap(pic, locationX, locationY, 0); }

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
  al_draw_rectangle(locationX, locationY, locationX + wid, locationY + hgt,
                    al_map_rgb(0, 0, 0), 2);
}
