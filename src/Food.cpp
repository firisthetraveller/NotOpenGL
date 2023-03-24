#include "Food.hpp"
#include "Config.hpp"
#include "glm/fwd.hpp"

Food::Food(glm::vec3 position, float radius)
    : _position(position), _radius(radius),
      _remainingBites(Config::getInstance().DEFAULT_FOOD_BITES) {}
