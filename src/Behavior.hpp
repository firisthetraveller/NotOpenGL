#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "Config.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/quaternion.hpp"
#include <functional>
#include <iostream>
#include <vector>

using Behavior = std::function<void(FishData &, std::vector<FishData> &)>;

class BehaviorFactory {
public:
  static Behavior wallTeleport() {
    return [](FishData &fish, [[maybe_unused]] std::vector<FishData> &others) {
      fish.teleport();
      // std::cout << "Teleport" << '\n';
    };
  }

  static Behavior wallAvoidance() {
    return [](FishData &fish, [[maybe_unused]] std::vector<FishData> &others) {
      if (fish._center.x < -Config::getInstance().ASPECT_RATIO +
                               Config::getInstance().WALL_MARGIN) {
        fish._movement.x += Config::getInstance().WALL_TURN_FACTOR;
      }
      if (fish._center.x > Config::getInstance().ASPECT_RATIO -
                               Config::getInstance().WALL_MARGIN) {
        fish._movement.x -= Config::getInstance().WALL_TURN_FACTOR;
      }
      if (fish._center.y < -1 + Config::getInstance().WALL_MARGIN) {
        fish._movement.y += Config::getInstance().WALL_TURN_FACTOR;
      }
      if (fish._center.y > 1 - Config::getInstance().WALL_MARGIN) {
        fish._movement.y -= Config::getInstance().WALL_TURN_FACTOR;
      }
      // std::cout << "Wall avoidance" << '\n';
    };
  }

  static Behavior speedLimiter() {
    return [](FishData &fish, [[maybe_unused]] std::vector<FishData> &others) {
      float speed = glm::length(fish._movement);

      if (speed > Config::getInstance().SPEED_LIMIT) {
        fish._movement *= Config::getInstance().SPEED_LIMIT / speed;
      }
      // std::cout << "Speed limiter" << '\n';
    };
  }

  static Behavior cohesion() {
    return [](FishData &fish, std::vector<FishData> &others) {
      unsigned int neighbors = 0;
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

      // std::cout << "Cohesion" << '\n';
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

      // std::cout << "Separation" << '\n';
    };
  }

  static Behavior alignment() {
    return [](FishData &fish, std::vector<FishData> &others) {
      unsigned int neighbors = 0;
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

      // std::cout << "Alignment" << '\n';
    };
  }
};

#endif
