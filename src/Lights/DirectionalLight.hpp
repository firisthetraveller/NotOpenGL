#ifndef __DIRECTIONAL_LIGHT__
#define __DIRECTIONAL_LIGHT__

#include <p6/p6.h>
#include "glm/fwd.hpp"

struct DirectionalLight {
  glm::vec4 _direction;
  glm::vec3 _intensity;
  glm::vec3 _rotationAxis;

  DirectionalLight(glm::vec4 direction, glm::vec3 intensity, glm::vec3 rotation)
    : _direction(direction), _intensity(intensity), _rotationAxis(rotation) {}

  glm::vec4 rotate(float angle) const;
};

#endif
