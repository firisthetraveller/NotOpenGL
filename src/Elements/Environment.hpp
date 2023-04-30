#ifndef __ENVIRONMENT_FISH__
#define __ENVIRONMENT_FISH__

#include "Elements/Fish/FishData.hpp"
#include "Elements/Food/Food.hpp"
#include "Elements/Obstacle/Obstacle.hpp"

#include <memory>
#include <vector>

struct Environment {
private:
  Environment() = default;

public:
  Environment(Environment &other) = delete;
  Environment(Environment &&move) = delete;
  std::vector<std::shared_ptr<FishData>> fishData;
  std::vector<std::shared_ptr<Food>> foods;
  std::vector<std::shared_ptr<Obstacle>> obstacles;

  static Environment &getInstance() {
    static Environment INSTANCE;

    return INSTANCE;
  }
};

#endif
