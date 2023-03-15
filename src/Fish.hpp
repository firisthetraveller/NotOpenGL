#ifndef __FISH__
#define __FISH__
#include "Behavior.hpp"
#include "FishData.hpp"
#include "glm/fwd.hpp"
#include <functional>
#include <p6/p6.h>
#include <vector>

class Fish {
private:
  FishData _data;
  std::vector<Behavior> _behaviors;

  void addDefaultBehaviors();

public:
  explicit Fish(const glm::vec2 &center, const p6::Radius &radius,
                const p6::Rotation &rotation, const glm::vec2 &movement);
  explicit Fish(const FishData &data);
  Fish(const Fish &other) = default;
  ~Fish() = default;

  bool operator==(const Fish &other) const;

  bool isOutOfBounds() const;
  bool isNear(Fish &other) const;

  FishData getData() const { return _data; }

  void draw(p6::Context &ctx);
  void addBehavior(Behavior behavior);
  void applyBehaviors(std::vector<FishData> &others);
  void update();

  static Fish generate();
};

// using Behavior = std::function<void(Fish &, std::vector<Fish> &)>;

#endif
