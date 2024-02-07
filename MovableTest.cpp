#ifndef PLAYER
#define PLAYER 1
#include "Player.h"
#endif
// #include <stdlib.h>

#include "Background.h"
#include "Enemy.h"
#include "time.h"
const int initialVel = -14;
const int immoveNum = 50;
int shootRate = 5;
const int maxBullets = 200;

void setImmovables(Immovable *immove[immoveNum], ALLEGRO_BITMAP *block,
                   ALLEGRO_BITMAP *buf);
void setEnemies(Enemy *enemies[50], ALLEGRO_BITMAP *, Player *);

void update_key(ALLEGRO_KEYBOARD_STATE &key, bool *keyboard_state) {
  al_get_keyboard_state(&key);
  for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
    keyboard_state[i] = al_key_down(&key, i);
  }
}

int real_main(int argc, char **argv) {
  srand(time(NULL));

  // initialize allegro
  al_init();

  // initialize keyboard
  al_install_keyboard();
  ALLEGRO_KEYBOARD_STATE keyboard_state;
  bool key[ALLEGRO_KEY_MAX];
  update_key(keyboard_state, key);

  // initialize audio
  al_install_audio();
  al_init_acodec_addon();
  // install_sound(DIGI_AUTODETECT, MIDI_NONE, "");

  // initialize display
  ALLEGRO_DISPLAY *disp = al_create_display(800, 600);
  // set_color_depth(16);
  // set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);
  // acquire_screen();
  ALLEGRO_BITMAP *buffer = al_create_bitmap(800, 600);

  // initialize font
  ALLEGRO_FONT *font = al_create_builtin_font();

  // initialize primitives
  al_init_primitives_addon();

  ALLEGRO_BITMAP *block = al_load_bitmap("Block.bmp");
  ALLEGRO_SAMPLE *gunshot = al_load_sample("gun.wav");
  ALLEGRO_SAMPLE *music = al_load_sample("UntoldStory.wav");
  ALLEGRO_SAMPLE *ivmusic = al_load_sample("starman.wav");
  ALLEGRO_SAMPLE *death = al_load_sample("zdeath.wav");
  ALLEGRO_SAMPLE *attack = al_load_sample("zattack.wav");

  Background b(0, 0, 800, 600, al_load_bitmap("SuperMarioBrosBackground.bmp"),
               buffer);
  Player c(150, 560, 50, 64, initialVel, initialVel, buffer, key);
  Immovable *immove[immoveNum];
  Movable *bullets[maxBullets];
  int bulletNum = 0, zombieKills = 0, score = 0, powerUpTime = 0,
      muzzaFuzza = 0;
  bool bulletDelay = false, powerUp = false, zombiePowerUp = false;
  int x;

  for (int i = 0; i < maxBullets; i++) {
    bullets[i] = NULL;
  }

  for (int i = 0; i < immoveNum; i++) immove[i] = NULL;

  setImmovables(immove, block, buffer);

  Enemy *enemies[50];
  for (int i = 0; i < 50; i++) enemies[i] = NULL;

  setEnemies(enemies, buffer, &c);

  al_draw_bitmap(al_load_bitmap("TitleScreen.bmp"), 0, 0, 0);

  while (!key[ALLEGRO_KEY_SPACE]) {
    al_draw_bitmap(buffer, 0, 0, 0);
  }
  // play_sample(music, 55, 128, 1000, 1);
  while (!key[ALLEGRO_KEY_ESCAPE]) {
    update_key(keyboard_state, key);

    // Bullets
    if (key[ALLEGRO_KEY_SPACE] && !bulletDelay) {
      for (int i = bulletNum; i > 0; i--) {
        bullets[i] = bullets[i - 1];
      }
      if (c.direction == 2) {
        bullets[0] = new Movable(
            c.locationX + 30, c.locationY + 29, 5, 3, initialVel, initialVel,
            buffer, al_load_bitmap("SmallBullet.bmp"), c.direction);
        muzzaFuzza = 2;
        al_draw_bitmap(al_load_bitmap("muzzafuzza.bmp"), c.locationX + 30,
                       c.locationY + 29, 0);
      }
      if (c.direction == 1) {
        bullets[0] = new Movable(
            c.locationX + 20, c.locationY + 29, 5, 3, initialVel, initialVel,
            buffer, al_load_bitmap("SmallBulletb.bmp"), c.direction);
        muzzaFuzza = 1;
        al_draw_bitmap(al_load_bitmap("muzzafuzza.bmp"), c.locationX + 30,
                       c.locationY + 29, 0);
      }
      bulletNum++;
      bulletDelay = true;
      // if (!powerUp) play_sample(gunshot, 35, 128, 1000, 0);
    }
    if (bulletDelay) {
      x++;
      if (x > shootRate) {
        x = 0;
        bulletDelay = false;
      }
    }

    for (int i = 0; i < 50; i++) {
      if (enemies[i] != NULL) {
        for (int n = 0; n < bulletNum; n++) {
          if (bullets[n] != NULL) {
            if (enemies[i]->checkCollision(
                    bullets[n]->locationX, bullets[n]->locationY,
                    bullets[n]->wid, bullets[n]->hgt) == 1) {
              enemies[i]->health -= 30;
              delete bullets[n];
              bullets[n] = NULL;
              break;
            }
          }
        }
      }
    }

    for (int i = 0; i < 50; i++) {
      if (enemies[i] != NULL) {
        if (enemies[i]->health <= 0) {
          // delete enemies[i];
          // enemies[i]=NULL;
          enemies[i]->locationX = 1000;
          enemies[i]->health = 100;
          // play_sample(death, 128, 128, 1000, 0);
          if (!powerUp) zombieKills++;
          score += 57;
        }
      }
    }

    if (zombieKills > 50) {
      powerUp = true;
      zombieKills = 0;
    }

    for (int i = 0; i < 50; i++) {
      if (enemies[i] != NULL) {
        if (enemies[i]->checkCollision(c.locationX, c.locationY, c.wid,
                                       c.hgt) == 1) {
          c.health -= 1;
          // al_load_sample(attack, 75, 128, 1000, 0);
        }
      }
    }

    if (c.health < 0) {
      c.locationX = 0;
      c.health = 200;
      c.locationY = 0;
      score -= 296;
      if (powerUp) {
        powerUp = false;
        shootRate = 5;
        powerUpTime = 0;
        // stop_sample(ivmusic);
        // play_sample(music, 75, 128, 1000, 1);
      }
    }

    for (int i = 0; i < bulletNum; i++) {
      if (bullets[i] != NULL) {
        if ((bullets[i]->locationX > 800) || (bullets[i]->locationX < 0)) {
          for (int n = i; n < bulletNum; n++) {
            delete bullets[n];
            bullets[n] = NULL;
          }
          bulletNum = i;
          break;
        }
      }
    }

    c.move();

    // Screen Scrolling
    if ((c.locationX >= 500) && (b.locationX > -8500)) {
      b.scrollScreen(1, 5);
      for (int i = 0; i < immoveNum; i++)
        if (immove[i] != NULL) immove[i]->move(5);
      for (int n = 0; n < 50; n++)
        if (enemies[n] != NULL) enemies[n]->scroll(5);
      c.locationX -= 13;
    } else if ((c.locationX <= 100) && (b.locationX < 0)) {
      for (int i = 0; i < immoveNum; i++)
        if (immove[i] != NULL) immove[i]->move(-5);
      for (int n = 0; n < 50; n++)
        if (enemies[n] != NULL) enemies[n]->scroll(-5);
      b.scrollScreen(2, 5);
      c.locationX += 13;
    } else {
      b.scrollScreen(1, 0);
    }

    // c.drawHitBox();

    // clear_to_color(buffer, al_map_rgb(5, 0, 0));
    b.display();
    c.display();
    for (int i = 0; i < immoveNum; i++)
      if (immove[i] != NULL) {
        immove[i]->display();
      }
    for (int i = 0; i < immoveNum; i++)
      if (immove[i] != NULL)
        c.checkPlatform(immove[i]->locationX, immove[i]->locationY,
                        immove[i]->wid, immove[i]->hgt);
    if (c.resetFloorHeight) c.floorHeight = 560;
    c.resetFloorHeight = true;
    // c.drawHitBox();
    // d.drawHitBox();

    for (int i = 0; i < 50; i++) {
      if (enemies[i] != NULL) {
        enemies[i]->display();
        // enemies[i]->displayName();
        // enemies[i]->drawHitBox();
        enemies[i]->move();
        for (int n = 0; n < immoveNum; n++) {
          if (immove[n] != NULL)
            enemies[i]->checkPlatform(immove[n]->locationX,
                                      immove[n]->locationY, immove[n]->wid,
                                      immove[n]->hgt);
        }
        if (enemies[i]->resetFloorHeight) enemies[i]->floorHeight = 560;
        enemies[i]->resetFloorHeight = true;
      }
    }
    // Moving bullets
    for (int i = 0; i < bulletNum; i++) {
      if (bullets[i] != NULL) {
        if (bullets[i]->direction == 2) bullets[i]->move(15, 0);
        if (bullets[i]->direction == 1) bullets[i]->move(-15, 0);
        bullets[i]->display();
        // bullets[i]->drawHitBox();
      }
    }
    if (powerUp) {
      if (key[ALLEGRO_KEY_W]) c.yVel -= 3;
      if (key[ALLEGRO_KEY_D]) c.xVel += 3;
      if (key[ALLEGRO_KEY_A]) c.xVel -= 3;
      if (key[ALLEGRO_KEY_S]) c.yVel += 3;
      shootRate = 0;
      powerUpTime++;
    }
    // TODO : Fix and reenable
    // if (powerUpTime == 1) {
    //   play_sample(ivmusic, 128, 128, 1000, 0);
    //   stop_sample(music);
    // }
    // if (powerUpTime == 666) {
    //   stop_sample(ivmusic);
    //   play_sample(music, 75, 128, 1000, 1);
    // }

    if (key[ALLEGRO_KEY_P]) zombiePowerUp = true;
    if (zombiePowerUp) {
      if (key[ALLEGRO_KEY_I]) {
        for (int i = 0; i < 50; i++) {
          if (enemies[i] != NULL) {
            enemies[i]->yVel -= 2;
          }
        }
      }
      if (key[ALLEGRO_KEY_K]) {
        for (int i = 0; i < 50; i++) {
          if (enemies[i] != NULL) {
            enemies[i]->yVel += 5;
          }
        }
      }
    }
    if (powerUpTime > 666) {
      powerUpTime = 0;
      powerUp = false;
      shootRate = 5;
    }
    al_draw_filled_rectangle(110, 10, c.health * 3 + 110, 15,
                             al_map_rgb(255, 0, 0));

    if (key[ALLEGRO_KEY_B]) powerUp = true;
    // TODO: Fix and reenable
    // textprintf_ex(buffer, font, 10, 10, al_map_rgb(0, 0, 0), -1, "Score: %d",
    //               score); //
    // if (powerUp)
    //   textprintf_ex(buffer, font, 350, 50,
    //                 al_map_rgb(rand() % 256, rand() % 256, rand() % 256), -1,
    //                 "POWERUP!!!");
    if (muzzaFuzza == 1) {
      al_draw_bitmap(al_load_bitmap("muzzafuzzab.bmp"), c.locationX - 23,
                     c.locationY + 25, 0);
      muzzaFuzza = 0;
    }
    if (muzzaFuzza == 2) {
      al_draw_bitmap(al_load_bitmap("muzzafuzza.bmp"), c.locationX + 45,
                     c.locationY + 25, 0);
      muzzaFuzza = 0;
    }
    al_draw_bitmap(buffer, 0, 0, 0);
    // clear_keybuf();
    al_rest(30);  // TODO: Implement a better way to handle frame rate
  }
  al_destroy_display(disp);
  // release_screen();
  return 0;
}
// END_OF_MAIN();

void setImmovables(Immovable *immove[immoveNum], ALLEGRO_BITMAP *block,
                   ALLEGRO_BITMAP *buf) {
  int i = 0;
  immove[i] = new Immovable(300, 495, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(600, 430, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(657, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(857, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(925, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(1200, 290, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(1400, 290, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(1122, 433, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(1854, 342, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2054, 342, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2254, 342, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(1575, 397, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(853, 494, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(1421, 494, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2500, 200, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2595, 425, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2700, 200, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2900, 200, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2400, 495, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2795, 425, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3041, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3241, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3441, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(2953, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3153, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3353, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3553, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3753, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3953, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(4153, 79, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(4237, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(4437, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(4637, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(4900, 431, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(4875, 230, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(5163, 329, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(5248, 230, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(5680, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(5480, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3770, 456, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(3970, 456, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6000, 248, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6000, 455, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6200, 150, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6200, 390, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6400, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6600, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(6800, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(7000, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(7200, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  immove[i] = new Immovable(7400, 341, 200, 15,
                            al_load_bitmap("BlockPlatform.bmp"), buf);
  i++;
  /*immove[i]=new Immovable(, , 200, 15, al_load_bitmap("BlockPlatform.bmp",
  NULL), buf); i++; immove[i]=new Immovable(, , 200, 15,
  al_load_bitmap("BlockPlatform.bmp"), buf); i++; immove[i]=new
  Immovable(, , 200, 15, al_load_bitmap("BlockPlatform.bmp"), buf); i++;
  immove[i]=new Immovable(, , 200, 15, al_load_bitmap("BlockPlatform.bmp",
  NULL), buf); i++;*/
}

void setEnemies(Enemy *enemies[50], ALLEGRO_BITMAP *buffer, Player *c) {
  int i = 0;
  enemies[i] = new Enemy(300, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(600, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(900, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(1200, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(1500, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(1800, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(2100, 0, 50, 64, initialVel, initialVel, buffer,
                         al_load_bitmap("zombiewalk.bmp"), c);
  i++;
}

int main(int argc, char **argv) { return al_run_main(argc, argv, real_main); }