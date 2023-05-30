#include "FishData.hpp"
#include "Config.hpp"
#include "glm/fwd.hpp"

FishData::FishData(unsigned int id, glm::vec3 center, float radius, float rotationX, float rotationY, glm::vec3 movement)
  : _id(id), _center(center), _radius(radius), _rotationX(rotationX), _rotationY(rotationY), _movement(movement) {}

static bool isOutOfBoundCoord(float coordinate, float limit = 1.0) {
  return (coordinate <= -limit || coordinate >= limit);
}

bool FishData::isOutOfBounds() const {
  return isOutOfBoundCoord(_center.x, Config::get().ASPECT_RATIO) || isOutOfBoundCoord(_center.y);
}

static float otherSide(float origin, float limit) {
  float calc = float(std::fmod((std::abs(origin) + limit), 2 * limit)) - limit;
  return (origin > 0) ? calc : -calc;
}

static float teleportIfOutOfBounds(float origin, float limit = 1.0f) {
  return (isOutOfBoundCoord(origin, limit)) ? otherSide(origin, limit) : origin;
}

void FishData::teleport() {
  _center = glm::vec3(
    teleportIfOutOfBounds(_center.x, Config::get().ASPECT_RATIO),
    teleportIfOutOfBounds(_center.y), teleportIfOutOfBounds(_center.z)
  );
}
