#include "Config.hpp"
#include "Elements/Fish/Fish.hpp"
#include "doctest/doctest.h"
#include "glm/fwd.hpp"
#include "internal/generate_range.hpp"
#include <memory>

// This is just an example of how to use Doctest in order to write tests.
// To learn more about Doctest, see
// https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
TEST_CASE("Random range is good") {
  for (unsigned int i = 0; i < 100; i++) {
    float tmp = generate_range(-5, 5);
    CHECK((tmp > -5.0 && tmp < 5.0));
  }
}

TEST_CASE("Boids are generated in the pond") {
  for (unsigned int i = 0; i < 100; i++) {
    Fish fish = Fish();
    CHECK((fish.getData()->_center.x > -1 && fish.getData()->_center.x < 1.0 &&
           fish.getData()->_center.y > -1 && fish.getData()->_center.y < 1.0));
  }
}

TEST_CASE("Boids can detect each other") {
  std::shared_ptr<Fish> fish = std::make_shared<Fish>();
  std::shared_ptr<Fish> fish2 = std::make_shared<Fish>(
      glm::vec2{fish->getData()->_center.x + Config::get().VISUAL_RANGE / 2,
                fish->getData()->_center.y},
      fish->getData()->_radius, fish->getData()->_rotation);

  CHECK((fish->isNear(fish2)));

  std::shared_ptr<Fish> fish3 = std::make_shared<Fish>(
      glm::vec2{fish->getData()->_center.x + 2 * Config::get().VISUAL_RANGE,
                fish->getData()->_center.y},
      fish->getData()->_radius, fish->getData()->_rotation);
  CHECK((!fish->isNear(fish3)));
}
