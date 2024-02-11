#include <iostream>
#include <utility>

#include "Background.h"
#include "Creature.h"
#include "Enemy.h"
#include "Immovable.h"
#include "Movable.h"
#include "Player.h"
#include "allegro.h"
#include "time.h"
#include "utils.h"

const int initialVel = -14;
const int immoveNum = 50;
int shootRate = 5;
const int maxBullets = 200;

void setImmovables(Immovable *immove[immoveNum], ALLEGRO_BITMAP *,
                   ALLEGRO_BITMAP *);
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

  ALLEGRO_VOICE *voice =
      al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

  ALLEGRO_MIXER *mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,
                                         ALLEGRO_CHANNEL_CONF_2);
  al_attach_mixer_to_voice(mixer, voice);

  int count = al_get_num_audio_output_devices();
  for (int i = 0; i < count; i++) {
    const ALLEGRO_AUDIO_DEVICE *device = al_get_audio_output_device(i);
    std::cout << ("%s\n", al_get_audio_device_name(device)) << std::endl;
  }
  al_reserve_samples(30);

  // initialize graphics
  al_init_image_addon();

  // initialize display
  ALLEGRO_DISPLAY *disp = al_create_display(800, 600);
  ALLEGRO_BITMAP *buffer = al_create_bitmap(800, 600);

  // initialize font
  ALLEGRO_FONT *font = al_create_builtin_font();

  // initialize primitives
  al_init_primitives_addon();

  ALLEGRO_BITMAP *blockplatform = load_bitmap("BlockPlatform.bmp");
  ALLEGRO_SAMPLE *gunshot = load_sample("gun.wav");
  ALLEGRO_SAMPLE *music = load_sample("UntoldStory.wav");
  ALLEGRO_SAMPLE *ivmusic = load_sample("starman.wav");
  ALLEGRO_SAMPLE *death = load_sample("zdeath.wav");
  ALLEGRO_SAMPLE *attack = load_sample("zattack.wav");

  Background b(0, 0, 800, 600, load_bitmap("SuperMarioBrosBackground.bmp"),
               buffer);
  Player c(150, 560, 50, 64, initialVel, initialVel, buffer, key);
  Immovable *immove[immoveNum];
  Movable *bullets[maxBullets];
  int bulletNum = 0, zombieKills = 0, score = 0, powerUpTime = 0,
      muzzaFuzza = 0;
  bool bulletDelay = false, powerUp = false, zombiePowerUp = false;
  int x = 0;

  for (int i = 0; i < maxBullets; i++) {
    bullets[i] = NULL;
  }

  for (int i = 0; i < immoveNum; i++) immove[i] = NULL;

  setImmovables(immove, blockplatform, buffer);

  Enemy *enemies[50];
  for (int i = 0; i < 50; i++) enemies[i] = NULL;

  setEnemies(enemies, buffer, &c);

  ALLEGRO_BITMAP *title_screen = load_bitmap("TitleScreen.bmp");
  al_draw_bitmap(title_screen, 0, 0, 0);
  al_flip_display();
  update_key(keyboard_state, key);
  while (!key[ALLEGRO_KEY_SPACE]) {
    update_key(keyboard_state, key);
  }

  al_play_sample(music, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
  al_set_voice_playing(voice, true);

  // main game loop
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
            buffer, load_bitmap_with_alpha("SmallBullet.bmp"), c.direction);
        muzzaFuzza = 2;
        al_draw_bitmap(load_bitmap_with_alpha("muzzafuzza.bmp"),
                       c.locationX + 30, c.locationY + 29, 0);
      }
      if (c.direction == 1) {
        bullets[0] = new Movable(
            c.locationX + 20, c.locationY + 29, 5, 3, initialVel, initialVel,
            buffer, load_bitmap_with_alpha("SmallBulletb.bmp"), c.direction);
        muzzaFuzza = 1;
        al_draw_bitmap(load_bitmap_with_alpha("muzzafuzza.bmp"),
                       c.locationX + 30, c.locationY + 29, 0);
      }
      bulletNum++;
      bulletDelay = true;
      if (!powerUp)
        al_play_sample(gunshot, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
          al_play_sample(death, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
          al_play_sample(attack, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
      al_draw_bitmap(load_bitmap_with_alpha("muzzafuzzab.bmp"),
                     c.locationX - 23, c.locationY + 25, 0);
      muzzaFuzza = 0;
    }
    if (muzzaFuzza == 2) {
      al_draw_bitmap(load_bitmap_with_alpha("muzzafuzza.bmp"), c.locationX + 45,
                     c.locationY + 25, 0);
      muzzaFuzza = 0;
    }
    al_flip_display();
    al_rest(0.03);  // TODO: Implement a better way to handle frame rate
  }
  al_destroy_display(disp);
  al_destroy_font(font);
  return 0;
}

void setImmovables(Immovable *immove[immoveNum], ALLEGRO_BITMAP *blockplatform,
                   ALLEGRO_BITMAP *buf) {
  const std::pair<int, int> platform_coords[] = {
      {300, 495},  {600, 430},  {657, 341},  {857, 341},  {925, 341},
      {1200, 290}, {1400, 290}, {1122, 433}, {1854, 342}, {2054, 342},
      {2254, 342}, {1575, 397}, {853, 494},  {1421, 494}, {2500, 200},
      {2595, 425}, {2700, 200}, {2900, 200}, {2400, 495}, {2795, 425},
      {3041, 341}, {3241, 341}, {3441, 341}, {2953, 79},  {3153, 79},
      {3353, 79},  {3553, 79},  {3753, 79},  {3953, 79},  {4153, 79},
      {4237, 341}, {4437, 341}, {4637, 341}, {4900, 431}, {4875, 230},
      {5163, 329}, {5248, 230}, {5680, 341}, {5480, 341}, {3770, 456},
      {3970, 456}, {6000, 248}, {6000, 455}, {6200, 150}, {6200, 390},
      {6400, 341}, {6600, 341}, {6800, 341}, {7000, 341}, {7200, 341},
      {7400, 341}};

  int i = 0;
  for (auto &coords : platform_coords) {
    immove[i] =
        new Immovable(coords.first, coords.second, 200, 15, blockplatform, buf);
    i++;
  }
}

void setEnemies(Enemy *enemies[50], ALLEGRO_BITMAP *buffer, Player *c) {
  int i = 0;
  enemies[i] = new Enemy(300, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(600, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(900, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(1200, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(1500, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(1800, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
  enemies[i] = new Enemy(2100, 0, 50, 64, initialVel, initialVel, buffer,
                         load_bitmap("zombiewalk.bmp"), c);
  i++;
}

int main(int argc, char **argv) { return al_run_main(argc, argv, real_main); }