#pragma once

#include <cstdio>
#include <functional>
#include <random>
#include <stdexcept>
#include <vector>

template <typename T> using Predicate = std::function<bool(T &)>;

/**
 * Create a vector that does not contain any element that doesn't match the
 * predicate.
 * @param vec : the original vector
 * @param predicate : the matching function
 * @return the filtered vector
 */
template <typename T>
std::vector<T> filter(std::vector<T> &vec, Predicate<T> predicate) {
  std::vector<T> result;
  for (T element : vec) {
    if (predicate(element)) {
      result.emplace_back(element);
    }
  }
  return result;
}
