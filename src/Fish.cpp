#include "Fish.hpp"
#include "Behavior.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"
#include "internal/generate_range.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <sys/types.h>
#include <utility>
#include <vector>

uint nextId() {
  static uint currentId = 0;
  return currentId++;
}

Fish::Fish(const glm::vec2 &center, const p6::Radius &radius,
           const p6::Rotation &rotation, const glm::vec2 &movement)
    : _data(FishData({nextId(), glm::vec3(center, 1), radius, rotation,
                      glm::vec3(movement, 0)})) {
  addDefaultBehaviors();
}

Fish::Fish(const FishData &data) : _data(data) { addDefaultBehaviors(); }

bool Fish::operator==(const Fish &other) const {
  return other._data == this->_data;
}

void Fish::addDefaultBehaviors() {
  _behaviors.emplace_back(BehaviorFactory::cohesion());
  _behaviors.emplace_back(BehaviorFactory::separation());
  _behaviors.emplace_back(BehaviorFactory::alignment());
  _behaviors.emplace_back(BehaviorFactory::teleport());
  _behaviors.emplace_back(BehaviorFactory::speedLimiter());
}

void Fish::addBehavior(Behavior behavior) { _behaviors.emplace_back(behavior); }

void Fish::applyBehaviors(std::vector<FishData> &others) {
  for (auto &behavior : _behaviors) {
    behavior(this->_data, others);
  }
}

void Fish::draw(p6::Context &ctx) {
  ctx.square(p6::Center(_data._center), _data._radius,
             p6::Rotation(p6::Angle{glm::vec2(_data._movement)}));
}

void Fish::update() {
  // Movement
  _data._center += _data._movement;
}

bool Fish::isNear(Fish &other) const { return _data.isNear(other.getData()); }

Fish Fish::generate() {
  return Fish(p6::random::point(), p6::Radius{generate_range(0.05, 0.1)},
              p6::Rotation{}, p6::random::direction() * 0.005f);
}
