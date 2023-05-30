#ifndef __FISHDATA__
#define __FISHDATA__

#include <p6/p6.h>
#include "Config.hpp"
#include "glm/fwd.hpp"

class FishData {
  private:
  const unsigned int _id;
  glm::vec3          _center;
  float              _radius;
  float              _rotationX;
  float              _rotationY;

  public:
  glm::vec3 _movement;

  FishData(unsigned int id, glm::vec3 center, float radius, float rotationX, float rotationY, glm::vec3 movement);

  // TODO operator == is expected to compare data fields
  bool operator==(const FishData& other) const { return _id == other._id; }

  bool         isOutOfBounds() const;
  unsigned int getId() const { return _id; };
  bool         isNear(const glm::vec3& position, float otherSize = 0.f, float distance = Config::get().VISUAL_RANGE) const;

  glm::vec3 getPosition() const { return _center; }
  float     getRotationX() const { return _rotationX; }
  float     getRotationY() const { return _rotationY; }
  float     getRadius() const { return _radius; }

  void teleport();
  void updatePosition(glm::vec3 translation) { _center += translation; };
};

#endif
