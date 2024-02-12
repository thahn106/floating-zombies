#include <stdlib.h>
#include <time.h>

#include "allegro.h"
#include "core/app.h"
#include "core/game.h"

void App::run() {
  srand(time(NULL));
  al_init();
  al_install_keyboard();

  al_install_audio();
  al_init_acodec_addon();

  al_init_image_addon();
  al_init_primitives_addon();
  // al_init_font_addon();

  ALLEGRO_DISPLAY* display = al_create_display(800, 600);
  ALLEGRO_FONT* font = al_create_builtin_font();

  Game game;
  game.init();

  while (true) {
    if (!game.update()) break;
    al_rest(0.016);  // TODO: fix implementation later
  }

  al_destroy_font(font);
  al_destroy_display(display);
  return;
}