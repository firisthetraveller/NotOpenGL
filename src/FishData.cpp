#include "FishData.hpp"

FishData::FishData(uint id, glm::vec3 center, p6::Radius radius,
                   p6::Rotation rotation, glm::vec3 movement)
    : _id(id), _center(center), _radius(radius), _rotation(rotation),
      _movement(movement) {}

bool isOutOfBoundCoord(float coordinate) {
  return (coordinate <= -1.0f || coordinate >= 1.0f);
}

bool FishData::isOutOfBounds() const {
  return isOutOfBoundCoord(_center.x) || isOutOfBoundCoord(_center.y);
}

float otherSide(float origin) {
  float calc = float(std::fmod((std::abs(origin) + 1.0f), 2.0f)) - 1.0f;
  return (origin > 0) ? calc : -calc;
}

float teleportIfOutOfBounds(float origin) {
  return (isOutOfBoundCoord(origin)) ? otherSide(origin) : origin;
}

bool FishData::isNear(const FishData &other, float distance) const {
  return glm::distance(this->_center, other._center) < distance;
}

void FishData::teleport() {
  _center = glm::vec3(glm::vec2(teleportIfOutOfBounds(_center.x),
                                teleportIfOutOfBounds(_center.y)),
                      1);
}
