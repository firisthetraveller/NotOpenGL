#ifndef __FISH__
#define __FISH__
#include <p6/p6.h>
#include <deque>
#include <memory>
#include <vector>
#include "Elements/Behavior.hpp"
#include "Elements/Environment.hpp"
#include "Elements/Food/Food.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include "internal/generate.hpp"

class Fish {
  private:
  std::shared_ptr<FishData> _data;
  std::vector<Behavior>     _behaviors;
  std::deque<glm::vec3>     _history;
  int                       _eatingCooldown;

  void addDefaultBehaviors();
  void applyBehaviors();
  void addHistory(const glm::vec3& position);

  public:
  Fish(const glm::vec3& center = Generate::point(), const float& radius = Generate::range(0.01f, 0.02f), const float& rotationX = 0.f, const float& rotationY = 0.f, const glm::vec3& movement = {});
  Fish(const Fish&) = delete;
  explicit Fish(std::shared_ptr<FishData> data);

  bool operator==(const Fish& other) const;

  const std::shared_ptr<FishData>& getData() const { return _data; }
  void                             showId();

  void eats(std::shared_ptr<Food>& food);
  bool canEat() const;

  void addBehavior(const Behavior& behavior);

  /**
   * Updates the fish after one tick.
   */
  void update();

  glm::vec3 getPosition() const { return _data->getPosition(); }
  float     getRotationX() const { return _data->getRotationX(); }
  float     getRotationY() const { return _data->getRotationY(); }
  float     getRadius() const { return _data->getRadius(); }
};

#endif
