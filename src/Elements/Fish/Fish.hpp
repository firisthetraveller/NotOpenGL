#ifndef __FISH__
#define __FISH__
#include "Elements/Behavior.hpp"
#include "Elements/Environment.hpp"
#include "Elements/Food/Food.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include "internal/generate_range.hpp"
#include <deque>
#include <memory>
#include <p6/p6.h>
#include <vector>

class Fish {
private:
  std::shared_ptr<FishData> _data;
  std::vector<Behavior> _behaviors;
  std::deque<glm::vec3> _history;
  int _eatingCooldown;

  void addDefaultBehaviors();
  void applyBehaviors();
  void addHistory(glm::vec3 &position);

public:
  Fish(const glm::vec2 &center = p6::random::point(),
       const p6::Radius &radius = p6::Radius{generate_range(0.01f, 0.02f)},
       const p6::Rotation &rotation = p6::Rotation{},
       const glm::vec2 &movement = {});
  Fish(const Fish &) = delete;
  explicit Fish(std::shared_ptr<FishData> data);

  bool operator==(const Fish &other) const;

  bool isOutOfBounds() const;
  bool isNear(std::shared_ptr<Fish> &other) const;

  const std::shared_ptr<FishData> &getData() const { return _data; }
  void showId();

  void eats(std::shared_ptr<Food> &food);
  bool canEat() const;

  void draw(p6::Context &ctx) const;
  void addBehavior(Behavior behavior);

  /**
   * Updates the fish after one tick.
   */
  void update();
};

#endif
