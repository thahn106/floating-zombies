#include "Background.h"
#include "allegro.h"

Background::Background(int xPos, int yPos, int xPos1, int yPos1,
                       ALLEGRO_BITMAP *picture, ALLEGRO_BITMAP *buffer)
    : Immovable(xPos, yPos, xPos1, yPos1, picture, buffer) {}
// function to move the background ALLEGRO_BITMAP
void Background::scrollScreen(int direction, int speed) {
  if (direction == 1) {
    locationX -= speed;
  } else if (direction == 2) {
    locationX += speed;
  }
  Immovable::display();
}