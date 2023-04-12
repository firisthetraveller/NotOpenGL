#include "Obstacle.hpp"
#include "../Config.hpp"

Obstacle::Obstacle(glm::vec2 center, float radius)
    : _center(glm::vec3{center, 1}), _radius(radius) {}

void Obstacle::draw(p6::Context &ctx) const {
  float baseStrokeWeight = ctx.stroke_weight;
  auto color = Config::getInstance().OBSTACLE_STROKE_COLOR;
  ctx.stroke = {color[0], color[1], color[2], color[3]};
  color = Config::getInstance().OBSTACLE_FILL_COLOR;
  ctx.fill = {color[0], color[1], color[2], color[3]};
  ctx.use_stroke = true;
  ctx.stroke_weight = baseStrokeWeight / 10.f;
  ctx.square(p6::Center{_center}, _radius);
  ctx.stroke_weight = baseStrokeWeight;
}
