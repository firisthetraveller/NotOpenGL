#include "Behavior.hpp"
#include "Config.hpp"
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
  Config::getInstance().ASPECT_RATIO = ctx.aspect_ratio();

  std::vector<Fish> fishs;
  std::vector<FishData> fishData;

  for (uint i = 0; i < 100; i++) {
    fishs.emplace_back(Fish::generate());
    // fishs[i].addBehavior(BehaviorFactory::teleport());
    fishData.emplace_back(fishs[i].getData());
  }

  // ImGui demo
  std::string text = "Hello";

  ctx.imgui = [&]() {
    ImGui::Begin("Parameters");
    ImGui::SliderFloat("Visual range", &Config::getInstance().VISUAL_RANGE, 0.f,
                       1.f);
    ImGui::SliderFloat("Vital space", &Config::getInstance().MIN_DISTANCE, 0.f,
                       0.3f);
    ImGui::SliderFloat("Speed limit", &Config::getInstance().SPEED_LIMIT, 0.f,
                       0.3f);
    ImGui::SliderFloat("Separation", &Config::getInstance().SEPARATION_FACTOR,
                       0.f, 1.f);
    ImGui::SliderFloat("Alignment", &Config::getInstance().ALIGNMENT_FACTOR,
                       0.f, 1.f);
    ImGui::SliderFloat("Cohesion", &Config::getInstance().COHESION_FACTOR, 0.f,
                       1.f);
    ImGui::SliderFloat("Wall margin", &Config::getInstance().WALL_MARGIN, 0.f,
                       0.5f);
    ImGui::SliderFloat("Wall turn", &Config::getInstance().WALL_TURN_FACTOR,
                       0.f, 0.5f);
    ImGui::End();
    // Show the official ImGui demo window
    // It is very useful to discover all the widgets available in ImGui
    // ImGui::ShowDemoWindow();
  };

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    // Comparison square
    // ctx.square(p6::Center{0, 0}, p6::Radius{1});

    for (Fish &fish : fishs) {
      fish.draw(ctx);
      fish.update();
      fish.applyBehaviors(fishData);
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}
