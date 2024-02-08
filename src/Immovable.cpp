#include "Immovable.h"
#include "allegro.h"

Immovable::Immovable(int xPos, int yPos, int xPos1, int yPos1,
                     ALLEGRO_BITMAP *picture, ALLEGRO_BITMAP *buffer) {
  locationX = xPos;  // top left corner
  locationY = yPos;
  wid = xPos1;  // width
  hgt = yPos1;
  pic = picture;
  buf = buffer;
}

void Immovable::display() { al_draw_bitmap(pic, locationX, locationY, 0); }
void Immovable::drawHitBox() {
  al_draw_rectangle(locationX, locationY, wid + locationX, hgt + locationY,
                    al_map_rgb(255, 0, 255), 2);
}

int Immovable::checkCollision(int x, int y, int w, int h) {
  if (x > locationX + wid) return 0;  // false
  if (x + w < locationX) return 0;
  if (y > locationY + hgt) return 0;
  if (y + h < locationY) return 0;
  return 1;
}

void Immovable::move(int x) { locationX -= x; }