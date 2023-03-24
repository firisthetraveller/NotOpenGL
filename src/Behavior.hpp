#ifndef __BEHAVIOR__
#define __BEHAVIOR__

#include "Config.hpp"
#include "Environment.hpp"
#include "FishData.hpp"
#include "Food.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using Behavior = std::function<void(FishData &, Environment &)>;

static float notXSq(float x) { return 1 - std::powf((x - 1), 32); }

class BehaviorFactory {
public:
  static Behavior wallTeleport() {
    return [](FishData &fish, [[maybe_unused]] Environment &) {
      fish.teleport();
      // std::cout << "Teleport" << '\n';
    };
  }

  static Behavior wallAvoidance() {
    return [](FishData &fish, [[maybe_unused]] Environment &) {
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
    return [](FishData &fish, [[maybe_unused]] Environment &) {
      float speed = glm::length(fish._movement);

      if (speed > Config::getInstance().SPEED_LIMIT) {
        fish._movement *= Config::getInstance().SPEED_LIMIT / speed;
      }
      // std::cout << "Speed limiter" << '\n';
    };
  }

  static Behavior foodSeeking() {
    return [](FishData &fish, Environment &env) {
      std::vector<std::pair<Food, float>> map;

      if (env.foods.empty()) {
        return;
      }
      for (Food &food : env.foods) {
        map.emplace_back(food, glm::distance(glm::vec2(food.getPosition()),
                                             glm::vec2(fish._center)) -
                                   food.getHitbox());
      }
      // Minimum
      auto min = std::accumulate(
          map.begin(), map.end(), map[0],
          [](std::pair<Food, float> p1, std::pair<Food, float> p2) {
            return (p1.second < p2.second) ? p1 : p2;
          });

      // std::cout << min.second << " - " << Config::getInstance().VISUAL_RANGE
      //           << '\n';
      // std::cout << "Fish is near? : " << fish.isNear(min.first) << '\n';
      // Overload movement
      if (fish.isNear(min.first)) {
        auto movement = min.first.getPosition() - fish._center;
        // std::cout << glm::length(movement) << " - "
        //           << notXSq(glm::length(movement)) / glm::length(movement)
        //           << '\n';
        fish._movement =
            movement * (notXSq(glm::length(movement)) / glm::length(movement));
        // std::cout << "Food detected !" << '\n';
      }
      // std::cout << "Food seeking" << '\n';
    };
  }

  static Behavior cohesion() {
    return [](FishData &fish, Environment &env) {
      unsigned int neighbors = 0;
      glm::vec3 center(0);

      for (FishData &other : env.fishData) {
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
    return [](FishData &fish, Environment &env) {
      glm::vec3 movement(0);
      for (FishData &other : env.fishData) {
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
    return [](FishData &fish, Environment &env) {
      unsigned int neighbors = 0;
      glm::vec3 alignmentVector(0);

      for (FishData &other : env.fishData) {
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
