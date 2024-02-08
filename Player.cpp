#include "Creature.h"
#include "Player.h"
#include "allegro.h"

Player::Player(int x, int y, int x2, int y2, int velX, int velY,
               ALLEGRO_BITMAP *buffer, bool *key)
    : Creature(x, y, x2, y2, velX, velY, buffer, al_load_bitmap("idle1.bmp")) {
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
  pics[0] = al_load_bitmap("crouch1.bmp");
  pics[1] = al_load_bitmap("crouch2.bmp");
  pics[2] = al_load_bitmap("crouch3.bmp");
  pics[3] = al_load_bitmap("crouch4.bmp");
  pics[4] = al_load_bitmap("idle1.bmp");
  pics[5] = al_load_bitmap("idle2.bmp");
  pics[6] = al_load_bitmap("idle3.bmp");
  pics[7] = al_load_bitmap("jump1.bmp");
  pics[8] = al_load_bitmap("jump2.bmp");
  pics[9] = al_load_bitmap("jump3.bmp");
  pics[10] = al_load_bitmap("jump4.bmp");
  pics[11] = al_load_bitmap("run6.bmp");
  pics[12] = al_load_bitmap("run5.bmp");
  pics[13] = al_load_bitmap("run4.bmp");
  pics[14] = al_load_bitmap("run3.bmp");
  pics[15] = al_load_bitmap("run2.bmp");
  pics[16] = al_load_bitmap("run1.bmp");
  pics[17] = al_load_bitmap("crouch1b.bmp");
  pics[18] = al_load_bitmap("crouch2b.bmp");
  pics[19] = al_load_bitmap("crouch3b.bmp");
  pics[20] = al_load_bitmap("crouch4b.bmp");
  pics[21] = al_load_bitmap("idle1b.bmp");
  pics[22] = al_load_bitmap("idle2b.bmp");
  pics[23] = al_load_bitmap("idle3b.bmp");
  pics[24] = al_load_bitmap("jump1b.bmp");
  pics[25] = al_load_bitmap("jump2b.bmp");
  pics[26] = al_load_bitmap("jump3b.bmp");
  pics[27] = al_load_bitmap("jump4b.bmp");
  pics[28] = al_load_bitmap("run6b.bmp");
  pics[29] = al_load_bitmap("run5b.bmp");
  pics[30] = al_load_bitmap("run4b.bmp");
  pics[31] = al_load_bitmap("run3b.bmp");
  pics[32] = al_load_bitmap("run2b.bmp");
  pics[33] = al_load_bitmap("run1b.bmp");
  this->key = key;
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
  if (key[ALLEGRO_KEY_UP]) {
    if (direction == 1) pic = pics[jumpCount % 4 + 24];
    if (direction == 2) pic = pics[jumpCount % 4 + 7];
  }
  if ((key[ALLEGRO_KEY_RIGHT]) && (!key[ALLEGRO_KEY_UP])) {
    pic = pics[walkCount % 6 + 11];
    if (slowWalk % 2 == 0) walkCount++;
    slowWalk++;
  }
  if ((key[ALLEGRO_KEY_LEFT]) && (!key[ALLEGRO_KEY_UP])) {
    pic = pics[walkCount % 6 + 28];
    if (slowWalk % 2 == 0) walkCount++;
    slowWalk++;
  }
  if ((key[ALLEGRO_KEY_DOWN]) && (!key[ALLEGRO_KEY_LEFT]) &&
      (!key[ALLEGRO_KEY_RIGHT]) && (!key[ALLEGRO_KEY_UP])) {
    if (direction == 2) pic = pics[3];
    if (direction == 1) pic = pics[20];
  }
  if ((!key[ALLEGRO_KEY_LEFT]) && (!key[ALLEGRO_KEY_RIGHT]) &&
      (!key[ALLEGRO_KEY_UP]) && (!key[ALLEGRO_KEY_DOWN])) {
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
  if (key[ALLEGRO_KEY_UP]) {
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
  if (key[ALLEGRO_KEY_RIGHT]) {
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
  if (key[ALLEGRO_KEY_LEFT]) {
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
    // textout_ex(buf, font, "FLOATING!!1", 10, 10, al_map_rgb(0, 0, 255), -1);
    jumping = true;
    // floorHeight=560;
  }
  if (checkCollision(b2_x, b2_y, b2_w, b2_h) == 1) {
    if ((locationY + hgt) >= b2_y && (locationY + hgt) <= (b2_y + 12)) {
      // textout_ex(buf, font, "UPPER HIT!!!", 10, 10, al_map_rgb(0, 0, 255),
      // -1);
      floorHeight = b2_y + 1;
      resetFloorHeight = false;
    } else if ((locationY <= (b2_y + b2_h)) && (locationY > b2_y)) {
      // textout_ex(buf, font, "LOWER HIT!!!", 10, 10, al_map_rgb(0, 0, 255),
      // -1);
      yVel = 4;
      jumping = false;
    } else if ((locationX + wid) >= b2_x && locationX <= b2_x) {
      // textout_ex(buf, font, "LEFT HIT!!!", 10, 10, al_map_rgb(0, 0, 255),
      // -1);
      locationX = (b2_x - wid);
      xVel = 0;
    } else if (locationX < (b2_x + b2_w)) {
      // textout_ex(buf, font, "RIGHT HIT!!!", 10, 10, al_map_rgb(0, 0, 255),
      // -1);
      locationX = (b2_x + b2_w);
      xVel = 0;
    }
  } else {
    // textout_ex(buf, font, "NO HIT!!", 10, 20, al_map_rgb(0, 0, 255), -1);
    // floorHeight=560;
  }
}