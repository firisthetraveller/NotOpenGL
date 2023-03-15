#ifndef __FISHDATA__
#define __FISHDATA__

#include "glm/fwd.hpp"
#include <p6/p6.h>

class FishData {
private:
  uint _id;

public:
  glm::vec3 _center;
  p6::Radius _radius;
  p6::Rotation _rotation;
  glm::vec3 _movement;

  FishData(uint id, glm::vec3 center, p6::Radius radius, p6::Rotation rotation,
           glm::vec3 movement);

  bool operator==(const FishData &other) const { return _id == other._id; }

  bool isOutOfBounds() const;
  bool isNear(const FishData &other) const;

  void teleport();
};

#endif
