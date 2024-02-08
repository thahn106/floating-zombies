#include <string>

#include "allegro.h"

const std::string ASSET_PATH = "assets/";
const std::string SPRITE_PATH = ASSET_PATH + "sprites/";
const std::string SOUND_PATH = ASSET_PATH + "sounds/";

ALLEGRO_BITMAP *load_bitmap(const std::string &file_name);
ALLEGRO_BITMAP *load_bitmap(const std::string &file_name, bool set_alpha);

std::string sprite_path(const std::string &sprite_name);
std::string sound_path(const std::string &sound_name);