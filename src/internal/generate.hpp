#pragma once

#include <algorithm>
#include <memory>
#include <random>
#include <stdexcept>
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_float3.hpp"

namespace Generate {
inline float range(float min, float max) {
  static std::random_device rand;
  static std::mt19937       mt32(rand());
  if (min > max) {
    throw std::invalid_argument("max should be bigger than min");
  }
  std::uniform_real_distribution<> reals(min, max);
  return float(reals(mt32));
}

inline glm::vec3 point(float min = -1.f, float max = 1.f) {
  return {range(min, max), range(min, max), range(min, max)};
}

inline glm::vec3 direction() {
  glm::vec3 p = point();
  return p / glm::length(p);
}

template<typename T>
std::vector<std::shared_ptr<T>> elements(int count) {
  std::vector<std::shared_ptr<T>> vec;
  vec.reserve(count);

  for (int i = 0; i < count; i++) {
    vec.emplace_back(std::make_shared<T>());
  }

  return vec;
}
}; // namespace Generate
