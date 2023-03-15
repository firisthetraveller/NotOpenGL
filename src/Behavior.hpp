#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "FishData.hpp"
#include <functional>

using Behavior = std::function<void(FishData &, std::vector<FishData> &)>;

class BehaviorFactory {
public:
  static Behavior teleport() {
    return [](FishData &fish, [[maybe_unused]] std::vector<FishData> &others) {
      fish.teleport();
    };
  }

  static Behavior alignment() {
    return [](FishData &fish, std::vector<FishData> &others) {
      for (FishData &other : others) {
        if (!(other == fish)) {
          if (fish.isNear(other)) {
          }
        }
      }
    };
  }
};

#endif
