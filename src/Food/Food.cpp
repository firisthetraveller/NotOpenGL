#include "Food.hpp"
#include "Config.hpp"
#include "glm/fwd.hpp"

Food::Food(glm::vec3 position, float radius)
    : _position(position), _radius(radius),
      _remainingBites(Config::get().DEFAULT_FOOD_BITES) {}

void Food::draw(p6::Context &ctx) const {
  float baseStrokeWeight = ctx.stroke_weight;
  auto color = Config::get().FOOD_COLOR;
  ctx.stroke = {color[0], color[1], color[2], color[3]};
  color = Config::get().FOOD_FILL_COLOR;
  ctx.fill = {color[0], color[1], color[2], color[3]};
  ctx.use_stroke = true;
  ctx.stroke_weight = baseStrokeWeight / 10.f;
  ctx.circle(p6::Center{_position}, _radius);
  ctx.stroke_weight = baseStrokeWeight;
}
