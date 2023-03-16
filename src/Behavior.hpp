#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "Config.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/quaternion.hpp"
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

  static Behavior speedLimiter() {
    return [](FishData &fish, [[maybe_unused]] std::vector<FishData> &others) {
      float speed = glm::length(fish._movement);

      if (speed > Config::getInstance().SPEED_LIMIT) {
        fish._movement *= Config::getInstance().SPEED_LIMIT / speed;
      }
    };
  }

  static Behavior cohesion() {
    return [](FishData &fish, std::vector<FishData> &others) {
      uint neighbors = 0;
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
        fish._movement +=
            (center - fish._center) * Config::getInstance().COHESION_FACTOR;
      }
    };
  }

  static Behavior separation() {
    return [](FishData &fish, std::vector<FishData> &others) {
      glm::vec3 movement(0);
      for (FishData &other : others) {
        if (other != fish) {
          if (fish.isNear(other, Config::getInstance().MIN_DISTANCE)) {
            movement += fish._center - other._center;
          }
        }
      }

      fish._movement += movement * Config::getInstance().SEPARATION_FACTOR;
    };
  }

  static Behavior alignment() {
    return [](FishData &fish, std::vector<FishData> &others) {
      uint neighbors = 0;
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
        fish._movement +=
            alignmentVector * Config::getInstance().ALIGNMENT_FACTOR;
      }
    };
  }
};

#endif
