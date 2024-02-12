#include <entt/entity/registry.hpp>

#include "allegro.h"
#include "comp/renderable.h"

void render(entt::registry& registry) {
  al_clear_to_color(al_map_rgb(0, 0, 0));
  for (auto entity : registry.view<Renderable>()) {
    auto& renderable = registry.get<Renderable>(entity);
    al_draw_bitmap(renderable.bitmap, renderable.x, renderable.y, 0);
  }
  al_flip_display();
}