#ifndef BACKGROUND_H
#define BACKGROUND_H

/*
    Background.h
    Class that will handle the background image
    Extends Immovable Objects
*/

#include "Immovable.h"
#include "allegro.h"
class Background : public Immovable {
 public:
  Background(int xPos, int yPos, int xPos1, int yPos1, ALLEGRO_BITMAP *picture,
             ALLEGRO_BITMAP *buffer);
  void scrollScreen(int direction, int speed);

 private:
};
#endif  // BACKGROUND_H