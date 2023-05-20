#include "Config.hpp"
#include "Elements/Fish/Fish.hpp"
#include "Elements/Positionable.hpp"
#include "doctest/doctest.h"
#include "glm/fwd.hpp"
#include "internal/generate.hpp"
#include <memory>

// This is just an example of how to use Doctest in order to write tests.
// To learn more about Doctest, see
// https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
TEST_CASE("Random range is good") {
  for (unsigned int i = 0; i < 100; i++) {
    float tmp = Generate::range(-5, 5);
    CHECK((tmp > -5.0 && tmp < 5.0));
  }
}

TEST_CASE("Boids are generated in the pond") {
  for (unsigned int i = 0; i < 100; i++) {
    Fish fish = Fish();
    CHECK((fish.getPosition().x > -1 && fish.getPosition().x < 1.0 &&
           fish.getPosition().y > -1 && fish.getPosition().y < 1.0 &&
           fish.getPosition().z > -1 && fish.getPosition().z < 1.0));
  }
}

TEST_CASE("Boids can detect each other") {
  std::shared_ptr<Fish> fish = std::make_shared<Fish>();
  std::shared_ptr<Fish> fish2 = std::make_shared<Fish>(
      glm::vec3{fish->getPosition().x + Config::get().VISUAL_RANGE / 2,
                fish->getPosition().y, fish->getPosition().z},
      fish->getRadius(), fish->getRotationX());

  CHECK((isNear(*fish, *fish2, Config::get().VISUAL_RANGE)));

  std::shared_ptr<Fish> fish3 = std::make_shared<Fish>(
      glm::vec3{fish->getPosition().x + fish->getRadius() +
                    2 * Config::get().VISUAL_RANGE,
                fish->getPosition().y, fish->getPosition().z},
      fish->getRadius(), fish->getRotationX());
  CHECK((!isNear(*fish, *fish3, Config::get().VISUAL_RANGE)));
}
