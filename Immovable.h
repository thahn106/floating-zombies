/*
    Immovable.h
    Header file for all immovable and static objects.
*/

class Immovable {
 public:
  Immovable(int xPos, int yPos, int xPos1, int yPos1, BITMAP *picture,
            BITMAP *buffer);
  void display();
  void drawHitBox();
  void move(int x);
  int checkCollision(int, int, int, int);
  int locationX;
  int locationY;
  int wid;
  int hgt;

 private:
  BITMAP *pic;
  BITMAP *buf;
};
// constructor
Immovable::Immovable(int xPos, int yPos, int xPos1, int yPos1, BITMAP *picture,
                     BITMAP *buffer) {
  locationX = xPos;  // top left corner
  locationY = yPos;
  wid = xPos1;  // width
  hgt = yPos1;
  pic = picture;
  buf = buffer;
}

void Immovable::display() { draw_sprite(buf, pic, locationX, locationY); }
void Immovable::drawHitBox() {
  rect(buf, locationX, locationY, wid + locationX, hgt + locationY,
       makecol(255, 0, 255));
}

int Immovable::checkCollision(int x, int y, int w, int h) {
  if (x > locationX + wid) return 0;  // false
  if (x + w < locationX) return 0;
  if (y > locationY + hgt) return 0;
  if (y + h < locationY) return 0;
  return 1;
}

void Immovable::move(int x) { locationX -= x; }
