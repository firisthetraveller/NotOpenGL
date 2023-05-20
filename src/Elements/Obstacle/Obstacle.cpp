#include "Obstacle.hpp"
#include "Config.hpp"
#include "internal/graphics.hpp"

Obstacle::Obstacle(glm::vec2 center, float radius)
    : _center(glm::vec3{center, 1}), _radius(radius) {}

