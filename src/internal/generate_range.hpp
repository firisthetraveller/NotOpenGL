#pragma once

#include <random>
#include <stdexcept>

inline float generate_range(float min, float max) {
  static std::random_device rand;
  static std::mt19937 mt32(rand());
  if (min > max) {
    throw std::invalid_argument("max should be bigger than min");
  }
  std::uniform_real_distribution<> reals(min, max);
  return float(reals(mt32));
}
