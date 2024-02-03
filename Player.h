/*
Player.h
This class is the player that moves using the arrow keys.
The player will have a bit of intertia when it moves and it will use a quadratic
to jump.
*/

#ifndef ALLEGRO
#define ALLEGRO 1
#include "Allegro.h"
#endif

#ifndef CREATURE
#define CREATURE 1
#include "Creature.h"
#endif

class Player : public Creature {
 public:
  Player(int x, int y, int x2, int y2, int velX, int velY, BITMAP *buffer);
  void move();
  void xvelocity();
  void yvelocity();
  void hit();
  void checkPlatform(int, int, int, int);
  void makeBullet(int xLoc, int yLoc, int direction);
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
  BITMAP *pics[34];
};

Player::Player(int x, int y, int x2, int y2, int velX, int velY, BITMAP *buffer)
    : Creature(x, y, x2, y2, velX, velY, buffer,
               load_bitmap("idle1.bmp", NULL)) {
  maxxVel = 13;
  picCount = 0;
  jumpCount = 0;
  walkCount = 0;
  idleCount = 0;
  idleRest = 0;
  slow = 0;
  slowWalk = 0;
  floorHeight = 560;
  resetFloorHeight = true;
  pics[0] = load_bitmap("crouch1.bmp", NULL);
  pics[1] = load_bitmap("crouch2.bmp", NULL);
  pics[2] = load_bitmap("crouch3.bmp", NULL);
  pics[3] = load_bitmap("crouch4.bmp", NULL);
  pics[4] = load_bitmap("idle1.bmp", NULL);
  pics[5] = load_bitmap("idle2.bmp", NULL);
  pics[6] = load_bitmap("idle3.bmp", NULL);
  pics[7] = load_bitmap("jump1.bmp", NULL);
  pics[8] = load_bitmap("jump2.bmp", NULL);
  pics[9] = load_bitmap("jump3.bmp", NULL);
  pics[10] = load_bitmap("jump4.bmp", NULL);
  pics[11] = load_bitmap("run6.bmp", NULL);
  pics[12] = load_bitmap("run5.bmp", NULL);
  pics[13] = load_bitmap("run4.bmp", NULL);
  pics[14] = load_bitmap("run3.bmp", NULL);
  pics[15] = load_bitmap("run2.bmp", NULL);
  pics[16] = load_bitmap("run1.bmp", NULL);
  pics[17] = load_bitmap("crouch1b.bmp", NULL);
  pics[18] = load_bitmap("crouch2b.bmp", NULL);
  pics[19] = load_bitmap("crouch3b.bmp", NULL);
  pics[20] = load_bitmap("crouch4b.bmp", NULL);
  pics[21] = load_bitmap("idle1b.bmp", NULL);
  pics[22] = load_bitmap("idle2b.bmp", NULL);
  pics[23] = load_bitmap("idle3b.bmp", NULL);
  pics[24] = load_bitmap("jump1b.bmp", NULL);
  pics[25] = load_bitmap("jump2b.bmp", NULL);
  pics[26] = load_bitmap("jump3b.bmp", NULL);
  pics[27] = load_bitmap("jump4b.bmp", NULL);
  pics[28] = load_bitmap("run6b.bmp", NULL);
  pics[29] = load_bitmap("run5b.bmp", NULL);
  pics[30] = load_bitmap("run4b.bmp", NULL);
  pics[31] = load_bitmap("run3b.bmp", NULL);
  pics[32] = load_bitmap("run2b.bmp", NULL);
  pics[33] = load_bitmap("run1b.bmp", NULL);
}

void Player::move() {
  yvelocity();
  xvelocity();
  locationX = locationX + xVel;
  locationY = locationY + yVel;
  if (jumping) {
    if ((jumpCount < 4) && (slow % 5 == 0)) {
      jumpCount++;
    }
    slow++;
  } else {
    jumpCount = 0;
  }
  if (key[KEY_UP]) {
    if (direction == 1) pic = pics[jumpCount % 4 + 24];
    if (direction == 2) pic = pics[jumpCount % 4 + 7];
  }
  if ((key[KEY_RIGHT]) && (!key[KEY_UP])) {
    pic = pics[walkCount % 6 + 11];
    if (slowWalk % 2 == 0) walkCount++;
    slowWalk++;
  }
  if ((key[KEY_LEFT]) && (!key[KEY_UP])) {
    pic = pics[walkCount % 6 + 28];
    if (slowWalk % 2 == 0) walkCount++;
    slowWalk++;
  }
  if ((key[KEY_DOWN]) && (!key[KEY_LEFT]) && (!key[KEY_RIGHT]) &&
      (!key[KEY_UP])) {
    if (direction == 2) pic = pics[3];
    if (direction == 1) pic = pics[20];
  }
  if ((!key[KEY_LEFT]) && (!key[KEY_RIGHT]) && (!key[KEY_UP]) &&
      (!key[KEY_DOWN])) {
    if (direction == 1) pic = pics[21 + idleCount % 3];
    if (direction == 2) pic = pics[4 + idleCount % 3];
    if (idleRest % 4 == 0) idleCount++;
    idleRest++;
  }
  if (locationY + hgt >= floorHeight) {
    yVel = -0.2 * yVel;
    locationY = floorHeight - hgt;
    jumping = false;
  }
  if (locationX <= 0) {
    xVel = 0;
    locationX = 0;
  }
  if (locationX >= 750) {
    xVel = 0;
    locationX = 750;
  }
  return;
}
void Player::yvelocity() {
  if (key[KEY_UP]) {
    if (jumping == false) {
      jumping = true;
      yVel = -15;
    }
    pic = pics[0];
  }
  if (jumping == true && yVel < 13) {
    yVel = yVel + 1;
  }
}
void Player::xvelocity() {
  if (key[KEY_RIGHT]) {
    if (xVel < maxxVel) {
      xVel++;
    }
    direction = 2;
    pic = pics[1];
  } else {
    if (xVel > 0) {
      xVel--;
    }
  }
  if (key[KEY_LEFT]) {
    if (xVel > -1 * maxxVel) {
      xVel--;
    }
    direction = 1;
  } else {
    if (xVel < 0) {
      xVel++;
    }
  }
}

void Player::makeBullet(int xLoc, int yLoc, int direction) {}

void Player::hit() {}

void Player::checkPlatform(int b2_x, int b2_y, int b2_w, int b2_h) {
  if ((locationY + hgt) < floorHeight &&
      checkCollision(b2_x, b2_y, b2_w, b2_h) == 0) {
    // textout_ex(buf, font, "FLOATING!!1", 10, 10, makecol(0, 0, 255), -1);
    jumping = true;
    // floorHeight=560;
  }
  if (checkCollision(b2_x, b2_y, b2_w, b2_h) == 1) {
    if ((locationY + hgt) >= b2_y && (locationY + hgt) <= (b2_y + 12)) {
      // textout_ex(buf, font, "UPPER HIT!!!", 10, 10, makecol(0, 0, 255), -1);
      floorHeight = b2_y + 1;
      resetFloorHeight = false;
    } else if ((locationY <= (b2_y + b2_h)) && (locationY > b2_y)) {
      // textout_ex(buf, font, "LOWER HIT!!!", 10, 10, makecol(0, 0, 255), -1);
      yVel = 4;
      jumping = false;
    } else if ((locationX + wid) >= b2_x && locationX <= b2_x) {
      // textout_ex(buf, font, "LEFT HIT!!!", 10, 10, makecol(0, 0, 255), -1);
      locationX = (b2_x - wid);
      xVel = 0;
    } else if (locationX < (b2_x + b2_w)) {
      // textout_ex(buf, font, "RIGHT HIT!!!", 10, 10, makecol(0, 0, 255), -1);
      locationX = (b2_x + b2_w);
      xVel = 0;
    }
  } else {
    // textout_ex(buf, font, "NO HIT!!", 10, 20, makecol(0, 0, 255), -1);
    // floorHeight=560;
  }
}
