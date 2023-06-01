#ifndef __DIRECTIONAL_LIGHT__
#define __DIRECTIONAL_LIGHT__

#include <p6/p6.h>

struct DirectionalLight {
  glm::vec4 _direction;
  glm::vec3 _intensity;

  DirectionalLight(glm::vec4 direction, glm::vec3 intensity)
    : _direction(direction), _intensity(intensity) {}
};

#endif
