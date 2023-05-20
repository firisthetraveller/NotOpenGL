#include "Fish.hpp"
#include "Config.hpp"
#include "Elements/Behavior.hpp"
#include "Elements/Environment.hpp"
#include "Elements/Food/Food.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "internal/graphics.hpp"
#include <iostream>
#include <memory>
#include <vector>

static unsigned int nextId() {
  static unsigned int currentId = 0;
  return currentId++;
}

Fish::Fish(const glm::vec2 &center, const float &radius, const float &rotationX,
           const float &rotationY, const glm::vec2 &movement)
    : _data(std::make_shared<FishData>(nextId(), glm::vec3(center, 1), radius,
                                       rotationX, rotationY,
                                       glm::vec3(movement, 0))),
      _eatingCooldown(0) {
  addDefaultBehaviors();
}

Fish::Fish(std::shared_ptr<FishData> data)
    : _data(std::move(data)), _eatingCooldown(0) {
  addDefaultBehaviors();
}

bool Fish::operator==(const Fish &other) const {
  return other._data == this->_data;
}

void Fish::addDefaultBehaviors() {
  _behaviors.emplace_back(BehaviorFactory::cohesion());
  _behaviors.emplace_back(BehaviorFactory::separation());
  _behaviors.emplace_back(BehaviorFactory::alignment());
  _behaviors.emplace_back(BehaviorFactory::avoidObstacles());
  _behaviors.emplace_back(BehaviorFactory::wallAvoidance());
  _behaviors.emplace_back(BehaviorFactory::foodSeeking());
  _behaviors.emplace_back(BehaviorFactory::alwaysActive());

  // Speed limit has to be at the end
  _behaviors.emplace_back(BehaviorFactory::speedLimiter());
}

void Fish::addBehavior(const Behavior &behavior) {
  _behaviors.emplace(_behaviors.end() - 1, behavior);
}

/***
 * Apply behaviors in the insert order.
 */
void Fish::applyBehaviors() {
  for (auto &behavior : _behaviors) {
    behavior(this->_data);
  }
}

void Fish::showId() { std::cout << _data->getId() << '\n'; }

void Fish::eats(std::shared_ptr<Food> &food) {
  _eatingCooldown =
      std::max(Config::get().FOOD_COOLDOWN_FRAMES,
               _eatingCooldown + Config::get().FOOD_COOLDOWN_FRAMES);
  food->getsBitten();
}

bool Fish::canEat() const { return _eatingCooldown < 0; }

void Fish::update() {
  applyBehaviors();
  addHistory(_data->getPosition());

  // Fullness
  _eatingCooldown--;

  // Movement
  _data->updatePosition(_data->_movement);
}

void Fish::addHistory(const glm::vec3 &position) {
  _history.push_front(position);
  int excess = static_cast<int>(_history.size()) - Config::get().HISTORY_SIZE;

  for (int i = 0; i < excess; i++) {
    _history.pop_back();
  }
}
