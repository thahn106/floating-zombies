#include <iostream>
#include <string>

#include "allegro.h"
#include "utils.h"

ALLEGRO_BITMAP *load_bitmap(const std::string &file_name) {
  const std::string file_path = sprite_path(file_name);
  ALLEGRO_BITMAP *bitmap = al_load_bitmap(file_path.c_str());
  if (!bitmap) {
    std::cerr << "Failed to load bitmap: " << file_path << std::endl;
  }
  return bitmap;
}

ALLEGRO_BITMAP *load_bitmap_with_alpha(const std::string &file_name) {
  ALLEGRO_BITMAP *bitmap = load_bitmap(file_name);
  al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 255));
  return bitmap;
}

ALLEGRO_SAMPLE *load_sample(const std::string &file_name) {
  const std::string file_path = sound_path(file_name);
  ALLEGRO_SAMPLE *sample = al_load_sample(file_path.c_str());
  if (!sample) {
    std::cerr << "Failed to load sample: " << file_path << std::endl;
  }
  return sample;
}

std::string sprite_path(const std::string &sprite_name) {
  return SPRITE_PATH + sprite_name;
}

std::string sound_path(const std::string &sound_name) {
  return SOUND_PATH + sound_name;
}