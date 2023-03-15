#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "FishData.hpp"
#include "glm/fwd.hpp"
#include <functional>
#include <vector>

using Behavior = std::function<void(FishData &, std::vector<FishData> &)>;

class BehaviorFactory {
public:
  static Behavior teleport() {
    return [](FishData &fish, [[maybe_unused]] std::vector<FishData> &others) {
      fish.teleport();
    };
  }

  static Behavior cohesion() {
    return [](FishData &fish, std::vector<FishData> &others) {
      uint neighbors = 0;
      const float COHESION_FACTOR = 0.005f;
      glm::vec3 center(0);

      for (FishData &other : others) {
        if (!(other == fish)) {
          if (fish.isNear(other)) {
            neighbors += 1;
            center += other._center;
          }
        }
      }

      if (neighbors != 0) {
        center /= neighbors;
        fish._movement += (center - fish._center) * COHESION_FACTOR;
      }
    };
  }

  static Behavior separation() {
    return [](FishData &fish, std::vector<FishData> &others) {
      const float MIN_DISTANCE = 20;
      // The distance to stay away from other boids

      const float AVOID_FACTOR = 0.05;
      // Adjust velocity by this %

      glm::vec3 movement(0);
      for (FishData &other : others) {
        if (other != fish) {
          if (fish.isNear(other, MIN_DISTANCE)) {
            movement += fish._center - other._center;
          }
        }
      }

      fish._movement += movement * AVOID_FACTOR;
    };
  }

  static Behavior alignment() {
    return [](FishData &fish, std::vector<FishData> &others) {
      uint neighbors = 0;
      const float ALIGNMENT_FACTOR = 0.02f;
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
