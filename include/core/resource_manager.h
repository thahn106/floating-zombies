#ifndef CORE_RESOURCE_MANAGER_H
#define CORE_RESOURCE_MANAGER_H

#include <vector>

#include "allegro.h"

class ResourceManager {
 public:
  ResourceManager(int num_bitmaps);
  ~ResourceManager();

  ALLEGRO_BITMAP* GetBitmap(std::size_t index);

  ALLEGRO_BITMAP* LoadBitmap(const char* filename);
  ALLEGRO_BITMAP* LoadBitmapWithAlpha(const char* filename);

 private:
  std::vector<ALLEGRO_BITMAP*> bitmaps;
};

#endif  // CORE_RESOURCE_MANAGER_H