#include "Config.hpp"
#include "Fish.hpp"
#include "doctest/doctest.h"
#include "internal/generate_range.hpp"

// This is just an example of how to use Doctest in order to write tests.
// To learn more about Doctest, see
// https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
TEST_CASE("Random range is good") {
  for (uint i = 0; i < 100; i++) {
    float tmp = generate_range(-5, 5);
    CHECK((tmp > -5.0 && tmp < 5.0));
  }
}

TEST_CASE("Boids are generated in the pond") {
  for (uint i = 0; i < 100; i++) {
    Fish fish = Fish();
    CHECK((fish.getData()._center.x > -1 && fish.getData()._center.x < 1.0 &&
           fish.getData()._center.y > -1 && fish.getData()._center.y < 1.0));
  }
}

TEST_CASE("Boids can detect each other") {
  Fish fish = Fish();
  Fish fish2 =
      Fish({fish.getData()._center.x + Config::getInstance().VISUAL_RANGE / 2,
            fish.getData()._center.y},
           fish.getData()._radius, fish.getData()._rotation, {0, 0});

  CHECK((fish.isNear(fish2)));

  Fish fish3 =
      Fish({fish.getData()._center.x + 2 * Config::getInstance().VISUAL_RANGE,
            fish.getData()._center.y},
           fish.getData()._radius, fish.getData()._rotation, {0, 0});
  CHECK((!fish.isNear(fish3)));
}
