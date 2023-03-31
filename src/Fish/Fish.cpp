#include "Fish.hpp"
#include "Behavior.hpp"
#include "Config.hpp"
#include "Environment.hpp"
#include "FishData.hpp"
#include "Food/Food.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
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
    : _data(std::make_shared<FishData>(nextId(), glm::vec3(center, 1), radius,
                                       rotation, glm::vec3(movement, 0))),
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
  _behaviors.emplace_back(BehaviorFactory::wallAvoidance());
  _behaviors.emplace_back(BehaviorFactory::foodSeeking());
  _behaviors.emplace_back(BehaviorFactory::alwaysActive());

  // Speed limit has to be at the end
  _behaviors.emplace_back(BehaviorFactory::speedLimiter());
}

void Fish::addBehavior(Behavior behavior) {
  _behaviors.emplace(_behaviors.end() - 1, behavior);
}

/***
 * Apply behaviors in the insert order.
 */
void Fish::applyBehaviors(Environment &env) {
  for (auto &behavior : _behaviors) {
    behavior(this->_data, env);
  }
}

void Fish::showId() { std::cout << _data->getId() << '\n'; }

void Fish::eats(std::shared_ptr<Food> &food) {
  _eatingCooldown =
      std::max(Config::getInstance().FOOD_COOLDOWN_FRAMES,
               _eatingCooldown + Config::getInstance().FOOD_COOLDOWN_FRAMES);
  food->getsBitten();
}

bool Fish::canEat() const { return _eatingCooldown < 0; }

void Fish::draw(p6::Context &ctx) const {
  float base_stroke_weight = ctx.stroke_weight;

  // showId();
  auto color = Config::getInstance().FISH_COLOR_1;
  ctx.stroke = {color[0], color[1], color[2], color[3]};
  ctx.fill = {color[0], color[1], color[2], color[3]};
  ctx.use_stroke = true;

  ctx.square(p6::Center{_data->_center}, _data->_radius,
             p6::Rotation(p6::Angle{glm::vec2(_data->_movement)}));

  if (Config::getInstance().SHOW_VISUAL_RANGES) {
    color = Config::getInstance().VISUAL_RANGE_COLOR;
    ctx.stroke = {color[0], color[1], color[2], color[3]};
    color = Config::getInstance().VISUAL_RANGE_FILL_COLOR;
    ctx.fill = {color[0], color[1], color[2], color[3]};
    ctx.use_stroke = true;
    ctx.stroke_weight = base_stroke_weight / 10.f;
    ctx.circle(p6::Center{_data->_center}, Config::getInstance().VISUAL_RANGE);
  }

  // Draw vision vector
  if (Config::getInstance().SHOW_MOVEMENT_VECTOR) {
    color = Config::getInstance().MOVEMENT_RANGE_COLOR;
    ctx.stroke = {color[0], color[1], color[2], color[3]};
    ctx.use_stroke = true;
    ctx.stroke_weight = base_stroke_weight / 10.f;
    glm::vec3 p2 = _data->_movement * 10.f;
    ctx.line(_data->_center, _data->_center + p2);
  }

  ctx.stroke_weight = base_stroke_weight;
}

void Fish::update() {
  // Fullness
  _eatingCooldown--;

  // Movement
  _data->_center += _data->_movement;
}

bool Fish::isNear(std::shared_ptr<Fish> &other) const {
  return _data->isNear(other->getData()->_center);
}
