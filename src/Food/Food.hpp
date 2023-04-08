#ifndef __FOOD__
#define __FOOD__

#include "Config.hpp"
#include "glm/fwd.hpp"
#include <p6/p6.h>
#include <vector>

class Food {
private:
  glm::vec3 _position;
  float _radius;
  int _remainingBites;

public:
  explicit Food(glm::vec3 position = {},
                float radius = Config::getInstance().DEFAULT_FOOD_SIZE);

  bool exists() const { return _remainingBites > 0; }
  int getRemainingBites() const { return _remainingBites; }
  glm::vec3 getPosition() const { return _position; }
  float getHitbox() const { return _radius; }
  void getsBitten() { _remainingBites -= 1; }

  void draw(p6::Context &ctx) const;
};

#endif
