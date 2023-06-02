#ifndef __BOUNDARY_OPENGL__
#define __BOUNDARY_OPENGL__

#include "Config.hpp"
#include "glm/ext/vector_float3.hpp"

struct Boundary {
  float height = Config::get().BOUNDARY_SIZE;

  glm::vec3 getPosition() { return {0, 0, 0}; };
  float     getRadius() { return height / 2; };
  float     getRotationX() { return 0.f; };
  float     getRotationY() { return 0.f; };
};

#endif
