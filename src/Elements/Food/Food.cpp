#include "Food.hpp"
#include "Config.hpp"
#include "Elements/Positionable.hpp"
#include "glm/fwd.hpp"
#include "internal/graphics.hpp"

Food::Food(glm::vec3 position, float radius)
    : _position(position), _radius(radius),
      _remainingBites(Config::get().DEFAULT_FOOD_BITES) {}

void Food::draw(p6::Context &ctx) const {
  Graphics::draw(
      ctx, [&]() { ctx.circle(p6::Center(_position), _radius); },
      Config::get().FOOD_COLOR, Config::get().FOOD_FILL_COLOR);
}
