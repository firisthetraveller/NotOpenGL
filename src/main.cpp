#include "Behavior.hpp"
#include "Fish.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include <cstdlib>
#include <memory>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char *argv[]) {
  { // Run the tests
    if (doctest::Context{}.run() != 0) {
      return EXIT_FAILURE;
    }
    // The CI does not have a GPU so it cannot run the rest of the code.
    const bool no_gpu_available =
        argc >= 2 &&
        strcmp(argv[1], "-nogpu") ==
            0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (no_gpu_available) {
      return EXIT_SUCCESS;
    }
  }

  // Actual app
  auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
  ctx.maximize_window();

  std::vector<Fish> fishs;
  std::vector<FishData> fishData;

  for (uint i = 0; i < 100; i++) {
    fishs.emplace_back(Fish::generate());
    fishs[i].addBehavior(BehaviorFactory::teleport());
    fishData.emplace_back(fishs[i].getData());
  }

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    ctx.square(p6::Center{0, 0}, p6::Radius{1});

    for (Fish &fish : fishs) {
      fish.draw(ctx);
      fish.update();
      fish.applyBehaviors(fishData);
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}
