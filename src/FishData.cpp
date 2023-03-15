#include "FishData.hpp"

static float NEAR_DISTANCE = 0.5f;

FishData::FishData(uint id, glm::vec3 center, p6::Radius radius,
                   p6::Rotation rotation, glm::vec3 movement)
    : _id(id), _center(center), _radius(radius), _rotation(rotation),
      _movement(movement) {}

bool isOutOfBoundCoord(float coordinate) {
  return (coordinate <= -1.f || coordinate >= 1.f);
}

bool FishData::isOutOfBounds() const {
  return isOutOfBoundCoord(_center.x) || isOutOfBoundCoord(_center.y);
}

float otherSide(float origin) {
  return float(std::fmod((origin + 1.0), 2.0)) - 1.0f;
}

float teleportIfOutOfBounds(float origin) {
  return (isOutOfBoundCoord(origin)) ? otherSide(origin) : origin;
}

bool FishData::isNear(const FishData &other) const {
  return glm::distance(this->_center, other._center) < NEAR_DISTANCE;
}

void FishData::teleport() {
  _center = glm::vec3(glm::vec2(teleportIfOutOfBounds(_center.x),
                                teleportIfOutOfBounds(_center.y)),
                      1);
}
