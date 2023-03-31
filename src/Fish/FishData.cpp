#include "FishData.hpp"
#include "Config.hpp"
#include "glm/fwd.hpp"
#include <memory>

FishData::FishData(unsigned int id, glm::vec3 center, p6::Radius radius,
                   p6::Rotation rotation, glm::vec3 movement)
    : _id(id), _center(center), _radius(radius), _rotation(rotation),
      _movement(movement) {}

static bool isOutOfBoundCoord(float coordinate, float limit = 1.0) {
  return (coordinate <= -limit || coordinate >= limit);
}

bool FishData::isOutOfBounds() const {
  return isOutOfBoundCoord(_center.x, Config::getInstance().ASPECT_RATIO) ||
         isOutOfBoundCoord(_center.y);
}

static float otherSide(float origin, float limit) {
  float calc = float(std::fmod((std::abs(origin) + limit), 2 * limit)) - limit;
  return (origin > 0) ? calc : -calc;
}

static float teleportIfOutOfBounds(float origin, float limit = 1.0f) {
  return (isOutOfBoundCoord(origin, limit)) ? otherSide(origin, limit) : origin;
}

bool FishData::isNear(const glm::vec3 &otherPosition, float otherSize,
                      float distance) const {
  return glm::distance(glm::vec2(this->_center), glm::vec2(otherPosition)) <
         (distance - otherSize);
}

void FishData::teleport() {
  _center =
      glm::vec3(glm::vec2(teleportIfOutOfBounds(
                              _center.x, Config::getInstance().ASPECT_RATIO),
                          teleportIfOutOfBounds(_center.y)),
                1);
}
