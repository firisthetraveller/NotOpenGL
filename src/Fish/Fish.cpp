#include "Fish.hpp"
#include "Behavior.hpp"
#include "Config.hpp"
#include "Environment.hpp"
#include "FishData.hpp"
#include "Food/Food.hpp"
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
  _behaviors.emplace_back(BehaviorFactory::avoidObstacles());
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

void Fish::draw(p6::Context &ctx) const {
  Graphics::draw(
      ctx,
      [&]() {
        ctx.equilateral_triangle(
            p6::Center{_data->_center}, _data->_radius,
            p6::Rotation(p6::Angle{glm::vec2(_data->_movement)}));
      },
      Config::get().FISH_1_COLOR, Config::get().FISH_1_FILL_COLOR);

  if (Config::get().SHOW_VISUAL_RANGES) {
    Graphics::draw(
        ctx,
        [&]() {
          ctx.circle(p6::Center{_data->_center}, Config::get().VISUAL_RANGE);
        },
        Config::get().VISUAL_RANGE_COLOR,
        Config::get().VISUAL_RANGE_FILL_COLOR);
  }

  // Draw vision vector
  if (Config::get().SHOW_MOVEMENT_VECTOR) {
    Graphics::draw(
        ctx,
        [&]() {
          glm::vec3 p2 = _data->_movement * 10.f;
          ctx.line(_data->_center, _data->_center + p2);
        },
        Config::get().MOVEMENT_RANGE_COLOR);
  }

  if (Config::get().SHOW_MOVEMENT_VECTOR) {
    Graphics::draw(
        ctx,
        [&]() {
          glm::vec3 p2 = _data->_movement * 10.f;
          ctx.line(_data->_center, _data->_center + p2);
        },
        Config::get().MOVEMENT_RANGE_COLOR);
  }

  if (Config::get().SHOW_POSITION_HISTORY) {
    static const int step = 10;
    for (unsigned int i = 0; i < _history.size() - step; i = i + step) {
      Graphics::draw(
          ctx, [&]() { ctx.line(_history[i], _history[i + step]); },
          Config::get().MOVEMENT_HISTORY_COLOR);
    }
  }
}

void Fish::update() {
  applyBehaviors();
  addHistory(_data->_center);

  // Fullness
  _eatingCooldown--;

  // Movement
  _data->_center += _data->_movement;
}

bool Fish::isNear(std::shared_ptr<Fish> &other) const {
  return _data->isNear(other->getData()->_center);
}

void Fish::addHistory(glm::vec3 &position) {
  _history.push_front(position);
  int excess = _history.size() - Config::get().HISTORY_SIZE;

  for (int i = 0; i < excess; i++) {
    _history.pop_back();
  }
}
