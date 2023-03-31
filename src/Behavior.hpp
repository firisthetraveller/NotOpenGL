#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "Config.hpp"
#include "Environment.hpp"
#include "Fish/FishData.hpp"
#include "Food/Food.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

using Behavior =
    std::function<void(std::shared_ptr<FishData> &, Environment &)>;

static float notXSq(float value) {
  return 1 - float(std::pow((value - 1), 32));
}

class BehaviorFactory {
public:
  static Behavior wallTeleport() {
    return [&](std::shared_ptr<FishData> &fish, Environment &) {
      fish->teleport();
      // std::cout << "Teleport" << '\n';
    };
  }

  static Behavior alwaysActive() {
    return [&](std::shared_ptr<FishData> &fish, Environment &) {
      if (glm::length(fish->_movement) <
          Config::getInstance().SPEED_LIMIT / 3) {
        fish->_movement = glm::vec3(p6::random::direction(), 0);
      }
    };
  }

  static Behavior wallAvoidance() {
    return [&](std::shared_ptr<FishData> &fish, Environment &) {
      if (fish->_center.x < -Config::getInstance().ASPECT_RATIO +
                                Config::getInstance().WALL_MARGIN) {
        fish->_movement.x += Config::getInstance().WALL_TURN_FACTOR;
      }
      if (fish->_center.x > Config::getInstance().ASPECT_RATIO -
                                Config::getInstance().WALL_MARGIN) {
        fish->_movement.x -= Config::getInstance().WALL_TURN_FACTOR;
      }
      if (fish->_center.y < -1 + Config::getInstance().WALL_MARGIN) {
        fish->_movement.y += Config::getInstance().WALL_TURN_FACTOR;
      }
      if (fish->_center.y > 1 - Config::getInstance().WALL_MARGIN) {
        fish->_movement.y -= Config::getInstance().WALL_TURN_FACTOR;
      }
      // std::cout << "Wall avoidance" << '\n';
    };
  }

  static Behavior speedLimiter() {
    return [&](std::shared_ptr<FishData> &fish, Environment &) {
      float speed = glm::length(fish->_movement);

      if (speed > Config::getInstance().SPEED_LIMIT) {
        fish->_movement *= Config::getInstance().SPEED_LIMIT / speed;
      }
      // std::cout << "Speed limiter" << '\n';
    };
  }

  static Behavior foodSeeking() {
    return [&](std::shared_ptr<FishData> &fish, Environment &env) {
      std::vector<std::pair<std::shared_ptr<Food>, float>> map;

      for (auto &food : env.foods) {
        if (!food->exists()) {
          continue;
        }

        float distance = glm::distance(glm::vec2(food->getPosition()),
                                       glm::vec2(fish->_center)) -
                         food->getHitbox();
        if (distance < Config::getInstance().VISUAL_RANGE) {
          map.emplace_back(food, distance);
        }
      }

      if (map.empty()) {
        std::cout << "map empty" << '\n';
        return;
      }
      std::cout << "map not empty" << '\n';

      // Minimum
      auto min = std::accumulate(
          map.begin(), map.end(), map[0],
          [](const std::pair<std::shared_ptr<Food>, float> &one,
             const std::pair<std::shared_ptr<Food>, float> &other) {
            return (one.second < other.second) ? one : other;
          });

      // std::cout << min.second << " - " << Config::getInstance().VISUAL_RANGE
      //           << '\n';
      // std::cout << "Fish is near? : " << fish.isNear(min.first) << '\n';

      // Overload movement
      if (fish->isNear(min.first->getPosition(), min.first->getHitbox())) {
        auto movement = min.first->getPosition() - fish->_center;
        // std::cout << glm::length(movement) << " - "
        //           << notXSq(glm::length(movement)) / glm::length(movement)
        //           << '\n';
        fish->_movement =
            movement * (notXSq(glm::length(movement)) / glm::length(movement));
        // std::cout << "Food detected !" << '\n';
      }
      // std::cout << "Food seeking" << '\n';
    };
  }

  static Behavior cohesion() {
    return [&](std::shared_ptr<FishData> &fish, Environment &env) {
      unsigned int neighbors = 0;
      glm::vec3 center(0);

      for (auto &other : env.fishData) {
        if (!(other.get() == fish.get())) {
          if (fish->isNear(other->_center)) {
            neighbors += 1;
            center += other->_center;
          }
        }
      }

      if (neighbors != 0) {
        center /= neighbors;
        fish->_movement +=
            (center - fish->_center) * Config::getInstance().COHESION_FACTOR;
      }

      // std::cout << "Cohesion" << '\n';
    };
  }

  static Behavior separation() {
    return [&](std::shared_ptr<FishData> &fish, Environment &env) {
      glm::vec3 movement(0);
      for (auto &other : env.fishData) {
        if (!(other.get() == fish.get())) {
          if (fish->isNear(other->_center, 0.0f,
                           Config::getInstance().MIN_DISTANCE)) {
            movement += fish->_center - other->_center;
          }
        }
      }

      fish->_movement += movement * Config::getInstance().SEPARATION_FACTOR;

      // std::cout << "Separation" << '\n';
    };
  }

  static Behavior alignment() {
    return [](std::shared_ptr<FishData> &fish, Environment &env) {
      unsigned int neighbors = 0;
      glm::vec3 alignmentVector(0);

      for (auto &other : env.fishData) {
        if (!(other.get() == fish.get())) {
          if (fish->isNear(other->_center)) {
            neighbors += 1;
            alignmentVector += other->_movement;
          }
        }
      }

      if (neighbors != 0) {
        alignmentVector /= neighbors;
        fish->_movement +=
            alignmentVector * Config::getInstance().ALIGNMENT_FACTOR;
      }

      // std::cout << "Alignment" << '\n';
    };
  }
};

#endif
