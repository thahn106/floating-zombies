#include "core/resource_manager.h"

#include "utils.h"

ResourceManager::ResourceManager(int num_bitmaps) {
  bitmaps.clear();
  bitmaps.reserve(num_bitmaps);
}

ResourceManager::~ResourceManager() {
  for (auto bitmap : bitmaps) {
    al_destroy_bitmap(bitmap);
  }
  bitmaps.clear();
}

ALLEGRO_BITMAP* ResourceManager::GetBitmap(std::size_t index) {
  if (index < 0 || index >= bitmaps.size()) {
    // fprintf(stderr, "Invalid bitmap index: %d\n", index);
    return NULL;
  }
  return bitmaps[index];
}

ALLEGRO_BITMAP* ResourceManager::LoadBitmap(const char* filename) {
  ALLEGRO_BITMAP* bitmap = load_bitmap(filename);
  if (bitmap == NULL) {
    // fprintf(stderr, "Failed to load bitmap: %s\n", filename);
    return NULL;
  }
  bitmaps.push_back(bitmap);
  return bitmap;
}

ALLEGRO_BITMAP* ResourceManager::LoadBitmapWithAlpha(const char* filename) {
  ALLEGRO_BITMAP* bitmap = load_bitmap_with_alpha(filename);
  if (bitmap == NULL) {
    // fprintf(stderr, "Failed to load bitmap: %s\n", filename);
    return NULL;
  }
  bitmaps.push_back(bitmap);
  return bitmap;
}