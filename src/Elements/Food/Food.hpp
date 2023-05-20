#ifndef __FOOD__
#define __FOOD__

#include "Config.hpp"
#include "glm/fwd.hpp"
#include <p6/p6.h>

class Food {
private:
  glm::vec3 _position;
  float _radius;
  int _remainingBites;

public:
  explicit Food(glm::vec3 position = {},
                float radius = Config::get().DEFAULT_FOOD_SIZE);

  bool exists() const { return _remainingBites > 0; }
  int getRemainingBites() const { return _remainingBites; }
  void getsBitten() { _remainingBites -= 1; }

  glm::vec3 getPosition() const { return _position; }
  float getRadius() const { return _radius; }
  float getRotationX() const { return 0.f; }
  float getRotationY() const { return 0.f; }
};

#endif
