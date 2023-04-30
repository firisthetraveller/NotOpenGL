#include "Obstacle.hpp"
#include "Config.hpp"
#include "internal/graphics.hpp"

Obstacle::Obstacle(glm::vec2 center, float radius)
    : _center(glm::vec3{center, 1}), _radius(radius) {}

void Obstacle::draw(p6::Context &ctx) const {
  Graphics::draw(
      ctx, [&]() { ctx.circle(p6::Center{_center}, _radius); },
      Config::get().OBSTACLE_STROKE_COLOR, Config::get().OBSTACLE_FILL_COLOR);
}
