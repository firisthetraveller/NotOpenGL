#include "Square.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include <cstdlib>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char *argv[]) {
  { // Run the tests
    if (doctest::Context{}.run() != 0)
      return EXIT_FAILURE;
    // The CI does not have a GPU so it cannot run the rest of the code.
    const bool no_gpu_available =
        argc >= 2 &&
        strcmp(argv[1], "-nogpu") ==
            0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (no_gpu_available)
      return EXIT_SUCCESS;
  }

  // Actual app
  auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
  ctx.maximize_window();

  std::vector<Square> squares = std::vector<Square>();

  for (uint i = 0; i < 100; i++) {
    squares.emplace_back(Square::generate());
  }

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    for (Square &square : squares) {
      square.draw(ctx);
      square.update();
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}
