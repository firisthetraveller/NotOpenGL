#include "Square.hpp"
#include "glm/fwd.hpp"
#include "internal/generate_range.hpp"

#include <algorithm>
#include <random>

Square::Square(p6::Center center, p6::Radius radius, p6::Rotation rotation,
               glm::vec2 movement)
    : _center(center), _radius(radius), _rotation(rotation),
      _movement(movement) {}

void Square::draw(p6::Context &ctx) { ctx.square(_center, _radius, _rotation); }

void Square::update() {
  _center =
      p6::Center{_center.value.x + _movement.x, _center.value.y + _movement.y};
}

Square Square::generate() {
  return Square(p6::random::point(), p6::Radius{generate_range(0, 0.3)},
                p6::Rotation{p6::random::angle()},
                p6::random::direction() * 0.01f);
}
