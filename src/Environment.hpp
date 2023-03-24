#ifndef __ENVIRONMENT_FISH__
#define __ENVIRONMENT_FISH__

#include "FishData.hpp"
#include "Food.hpp"
#include <vector>

struct Environment {
private:
  Environment() = default;

public:
  Environment(Environment &other) = delete;
  Environment(Environment &&move) = delete;
  std::vector<FishData> fishData;
  std::vector<Food> foods;

  static Environment &getInstance() {
    static Environment INSTANCE;

    return INSTANCE;
  }
};

#endif
