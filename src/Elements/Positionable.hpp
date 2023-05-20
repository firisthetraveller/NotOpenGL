#ifndef __DRAWABLE__
#define __DRAWABLE__

#include "Config.hpp"
#include "Elements/Food/Food.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <concepts>
#include <iostream>
#include <p6/p6.h>

template <typename T>
concept is_positionable = requires(T element) {
  { element.getPosition() } -> std::convertible_to<glm::vec3>;
  { element.getRotationX() } -> std::convertible_to<float>;
  { element.getRotationY() } -> std::convertible_to<float>;
  { element.getRadius() } -> std::convertible_to<float>;
};

template <is_positionable P> glm::mat4 getModelMatrix(P &element) {
  return glm::rotate(glm::mat4{1.f}, element.getRotationX(), {1, 0, 0}) *
         glm::rotate(glm::mat4{1.f}, element.getRotationY(), {0, 1, 0}) *
         glm::translate(glm::mat4{1.f}, element.getPosition()) *
         glm::scale(glm::mat4{1.f},
                    glm::vec3{1.f, 1.f, 1.f} * element.getRadius());
}

template <is_positionable P, is_positionable Q>
bool isNear(P &first, Q &second, float threshold, bool debug = false) {
  float distance = glm::distance(glm::vec2(first.getPosition()),
                                 glm::vec2(second.getPosition()));
  float range = threshold + first.getRadius() + second.getRadius();

  if (debug) {
    std::cout << "distance: " << distance << "\n";
    std::cout << "threshold: " << range << "\n";
  }
  return distance < range;
};

template <is_positionable P> class Positionable : public P {};

#endif
