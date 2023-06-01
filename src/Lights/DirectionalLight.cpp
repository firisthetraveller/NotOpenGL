#include "DirectionalLight.hpp"
#include "glm/gtx/rotate_vector.hpp"

glm::vec4 DirectionalLight::rotate(float angle) const {
  return glm::rotate(glm::mat4{1.f}, angle, _rotationAxis) * _direction;
}
