#include "Obstacle.hpp"
#include "Config.hpp"
#include "internal/graphics.hpp"

Obstacle::Obstacle(glm::vec3 center, float radius)
  : _center(center), _radius(radius) {}
