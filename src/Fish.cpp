#include "Fish.hpp"
#include "Behavior.hpp"
#include "Config.hpp"
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

static unsigned int nextId() {
  static unsigned int currentId = 0;
  return currentId++;
}

Fish::Fish(const glm::vec2 &center, const p6::Radius &radius,
           const p6::Rotation &rotation, const glm::vec2 &movement)
    : _data(FishData({
          nextId(),
          glm::vec3(center, 1),
          radius,
          rotation,
          glm::vec3(movement, 0),
      })) {
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
  _behaviors.emplace_back(BehaviorFactory::wallAvoidance());

  // Speed limit has to be at the end
  _behaviors.emplace_back(BehaviorFactory::speedLimiter());
}

void Fish::addBehavior(Behavior behavior) {
  _behaviors.emplace(_behaviors.end() - 1, behavior);
}

/***
 * Apply behaviors in the insert order.
 */
void Fish::applyBehaviors(std::vector<FishData> &others) {
  for (auto &behavior : _behaviors) {
    behavior(this->_data, others);
  }
}

void Fish::showId() { std::cout << _data.getId() << '\n'; }

void Fish::draw(p6::Context &ctx) {
  // showId();
  ctx.square(p6::Center{_data._center}, _data._radius,
             p6::Rotation(p6::Angle{glm::vec2(_data._movement)}));

  ctx.circle(p6::Center{_data._center}, Config::getInstance().VISUAL_RANGE);

  // Draw vision vector
  glm::vec3 p2 = _data._movement * 10.f;
  ctx.line(_data._center, _data._center + p2);
}

void Fish::update() {
  // Movement
  _data._center += _data._movement;
}

bool Fish::isNear(Fish &other) const { return _data.isNear(other.getData()); }

Fish Fish::generate() {
  return Fish(p6::random::point(), p6::Radius{generate_range(0.005, 0.0075)},
              p6::Rotation{}, p6::random::direction() * 0.005f);
}
