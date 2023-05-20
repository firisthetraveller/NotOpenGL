#include "Food.hpp"
#include "Config.hpp"
#include "Elements/Positionable.hpp"
#include "glm/fwd.hpp"
#include "internal/graphics.hpp"

Food::Food(glm::vec3 position, float radius)
    : _position(position), _radius(radius),
      _remainingBites(Config::get().DEFAULT_FOOD_BITES) {}
