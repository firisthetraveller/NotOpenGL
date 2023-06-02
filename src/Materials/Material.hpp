#ifndef __MATERIAL_OPENGL__
#define __MATERIAL_OPENGL__

#include <p6/p6.h>
#include "glm/fwd.hpp"

struct Material {
  glm::vec3 _diffuse;
  glm::vec3 _specular;
  float     _shininess;

  Material(const glm::vec3& diffuse = glm::vec3{0.f}, const glm::vec3& specular = glm::vec3{0.f}, float shininess = 0.f)
    : _diffuse(diffuse), _specular(specular), _shininess(shininess){};
};

#endif
