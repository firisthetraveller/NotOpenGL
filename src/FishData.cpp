#include "FishData.hpp"
#include "Config.hpp"

FishData::FishData(uint id, glm::vec3 center, p6::Radius radius,
                   p6::Rotation rotation, glm::vec3 movement)
    : _id(id), _center(center), _radius(radius), _rotation(rotation),
      _movement(movement) {}

bool isOutOfBoundCoord(float coordinate, float limit = 1.0) {
  return (coordinate <= -limit || coordinate >= limit);
}

bool FishData::isOutOfBounds() const {
  return isOutOfBoundCoord(_center.x, Config::getInstance().ASPECT_RATIO) ||
         isOutOfBoundCoord(_center.y);
}

float otherSide(float origin, float limit) {
  float calc = float(std::fmod((std::abs(origin) + limit), 2 * limit)) - limit;
  return (origin > 0) ? calc : -calc;
}

float teleportIfOutOfBounds(float origin, float limit = 1.0f) {
  return (isOutOfBoundCoord(origin, limit)) ? otherSide(origin, limit) : origin;
}

bool FishData::isNear(const FishData &other, float distance) const {
  return glm::distance(this->_center, other._center) < distance;
}

void FishData::teleport() {
  _center =
      glm::vec3(glm::vec2(teleportIfOutOfBounds(
                              _center.x, Config::getInstance().ASPECT_RATIO),
                          teleportIfOutOfBounds(_center.y)),
                1);
}
