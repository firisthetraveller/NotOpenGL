#ifndef __NO_OBSTACLE__
#define __NO_OBSTACLE__

#include <p6/p6.h>

struct Obstacle {
  glm::vec3 _center;
  float _radius;

  Obstacle(glm::vec2 center = p6::random::point(), float radius = 0.1f);
  void draw(p6::Context &ctx) const;

  glm::vec3 getPosition() const { return _center; }
  float getRotationX() const { return 0.f; }
  float getRotationY() const { return 0.f; }
  float getRadius() const { return _radius; }
};

#endif
