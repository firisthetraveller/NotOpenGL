#ifndef __FISH__
#define __FISH__
#include "glm/fwd.hpp"
#include <functional>
#include <p6/p6.h>
#include <vector>

#include "Behavior.hpp"
#include "FishData.hpp"
#include "internal/generate_range.hpp"

class Fish {
private:
  FishData _data;
  std::vector<Behavior> _behaviors;

  void addDefaultBehaviors();

public:
  Fish(const glm::vec2 &center = p6::random::point(),
       const p6::Radius &radius = p6::Radius{generate_range(0.005, 0.0075)},
       const p6::Rotation &rotation = p6::Rotation{},
       const glm::vec2 &movement = p6::random::direction() * 0.005f);
  explicit Fish(const FishData &data);

  bool operator==(const Fish &other) const;

  bool isOutOfBounds() const;
  bool isNear(Fish &other) const;

  const FishData &getData() const { return _data; }
  void showId();

  void draw(p6::Context &ctx);
  void addBehavior(Behavior behavior);
  void applyBehaviors(std::vector<FishData> &others);
  void update();
};

// using Behavior = std::function<void(Fish &, std::vector<Fish> &)>;

#endif
