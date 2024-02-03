/*
    Background.h
    Class that will handle the background image
    Extends Immovable Objects
*/


#include "Immovable.h"

using namespace std;

class Background : public Immovable {
      public:
            Background(int xPos, int yPos, int xPos1, int yPos1, BITMAP *picture, BITMAP *buffer);
            void scrollScreen(int direction, int speed); 
      private:
      
};
// constructor
Background::Background(int xPos, int yPos, int xPos1, int yPos1, BITMAP *picture, BITMAP *buffer)
: Immovable(xPos, yPos, xPos1, yPos1, picture, buffer)
{
}
// function to move the background bitmap
void Background::scrollScreen(int direction, int speed) {
     if(direction==1){
          locationX-=speed;
     } else if (direction==2){
            locationX+=speed;
     }
     Immovable::display();
}
