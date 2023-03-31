#pragma once

#include <algorithm>
#include <cstdio>
#include <functional>
#include <random>
#include <ranges>
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
  //  Does not work with Clang :(
  //  return vec | std::views::filter(predicate);
  std::vector<T> tmp;

  for (T item : vec) {
    if (predicate(item)) {
      tmp.emplace_back(item);
    }
  }

  return tmp;
}
