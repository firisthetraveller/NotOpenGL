#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "FishData.hpp"
#include "glm/fwd.hpp"
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
      uint neighbors = 0;
      const float ALIGNMENT_FACTOR = 0.005f;
      glm::vec3 alignmentVector(0);

      for (FishData &other : others) {
        if (!(other == fish)) {
          if (fish.isNear(other)) {
            neighbors += 1;
            alignmentVector += other._movement;
          }
        }
      }

      if (neighbors != 0) {
        alignmentVector /= neighbors;
        fish._movement += alignmentVector * ALIGNMENT_FACTOR;
      }
    };
  }
};

#endif
