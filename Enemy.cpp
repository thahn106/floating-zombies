#include "Creature.h"
#include "Enemy.h"
#include "Player.h"
#include "allegro.h"
Enemy::Enemy(int x, int y, int width, int height, int velX, int velY,
             ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *picture, Player *playa)
    : Creature(x, y, width, height, velX, velY, buffer, picture) {
  player = playa;
  floorHeight = 560;
  resetFloorHeight = true;
  xVel = 0;
  yVel = 0;
  jumping = false;
  speed = (rand() % 6) + 1;
  picCount = 0;
}

void Enemy::scroll(int x) { locationX -= x; }

void Enemy::move() {
  xVelocity();
  yVelocity();
  locationX += xVel;
  locationY += yVel;
  if (locationY + hgt >= floorHeight) {
    jumping = false;
    yVel = 0;
    locationY = floorHeight - hgt;
  }
}
void Enemy::xVelocity() {
  if ((player->locationX) < (locationX)) {
    xVel = -(speed);
    if (picCount % 12 == 0) pic = al_load_bitmap("zombiewalkb.bmp");
    if (picCount % 12 == 2) pic = al_load_bitmap("zombiewalk2b.bmp");
    if (picCount % 12 == 4) pic = al_load_bitmap("zombiewalk3b.bmp");
    if (picCount % 12 == 6) pic = al_load_bitmap("zombiewalk4b.bmp");
    if (picCount % 12 == 8) pic = al_load_bitmap("zombiewalk5b.bmp");
    if (picCount % 12 == 10) pic = al_load_bitmap("zombiewalk6b.bmp");
    picCount++;
  } else if ((player->locationX) > (locationX)) {
    xVel = speed;
    if (picCount % 12 == 0) pic = al_load_bitmap("zombiewalk.bmp");
    if (picCount % 12 == 2) pic = al_load_bitmap("zombiewalk2.bmp");
    if (picCount % 12 == 4) pic = al_load_bitmap("zombiewalk3.bmp");
    if (picCount % 12 == 6) pic = al_load_bitmap("zombiewalk4.bmp");
    if (picCount % 12 == 8) pic = al_load_bitmap("zombiewalk5.bmp");
    if (picCount % 12 == 10) pic = al_load_bitmap("zombiewalk6.bmp");
    picCount++;
  } else if ((player->locationX) == (locationX)) {
    xVel = 0;
    // pic=al_load_bitmap("zombiewalk.bmp");
  }
  if (picCount == 12) picCount = 0;
}
void Enemy::yVelocity() {
  if ((player->locationY) < (locationY)-70) jumping = true;
  if (jumping == true) yVel = -12;
  if (jumping == false && yVel < 5) {
    yVel = yVel + 1;
  }
  if (yVel == 0 || jumping) jumping = false;
}
void Enemy::displayName() {
  // textout_ex(buf, font, "Enemah!", locationX, locationY - 10,
  //            al_map_rgb(0, 0, 255), -1);
  // TODO: Implement this
  // al_draw_text(font, al_map_rgb(0, 0, 255), locationX, locationY - 10,
  //              ALLEGRO_ALIGN_CENTRE, "Enemah!");
}
void Enemy::checkPlatform(int b2_x, int b2_y, int b2_w, int b2_h) {
  if ((locationY + hgt) < floorHeight &&
      checkCollision(b2_x, b2_y, b2_w, b2_h) == 0) {
    // textout_ex(buf, font, "FLOATING!!1", 100, 10, al_map_rgb(0, 0, 255), -1);
    jumping = false;
    floorHeight = 560;
  }
  if (checkCollision(b2_x, b2_y, b2_w, b2_h) == 1) {
    if ((locationY <= (b2_y + b2_h)) && (locationY > b2_y)) {
      // textout_ex(buf, font, "LOWER HIT!!!", 10, 10, al_map_rgb(0, 0, 255),
      // -1);
      yVel = 4;
      jumping = false;
    } else if ((locationY + hgt) >= b2_y &&
               (locationY + hgt) <= (b2_y + (b2_h / 2))) {
      // textout_ex(buf, font, "UPPER HIT!!!", 100, 10, al_map_rgb(0, 0, 255),
      // -1);
      floorHeight = b2_y + 1;
      resetFloorHeight = false;
    }

    else if ((locationX + wid) >= b2_x && locationX <= b2_x) {
      // textout_ex(buf, font, "LEFT HIT!!!", 100, 10, al_map_rgb(0, 0, 255),
      // -1);
      locationX = (b2_x - wid);
      locationX -= 5;
      xVel = 0;
      jumping = true;
    } else if (locationX < (b2_x + b2_w)) {
      // textout_ex(buf, font, "RIGHT HIT!!!", 100, 10, al_map_rgb(0, 0, 255),
      // -1);
      locationX = (b2_x + b2_w);
      locationX += 5;
      xVel = 0;
      jumping = true;
    }
  } else {
    // textout_ex(buf, font, "NO HIT!!", 100, 20, al_map_rgb(0, 0, 255), -1);
    // floorHeight=560;
    // resetFloorHeight=true;
  }
}
