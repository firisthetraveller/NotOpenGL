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
