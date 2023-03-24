#include "Behavior.hpp"
#include "Config.hpp"
#include "Fish.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
#include <cstdlib>
#include <memory>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

static std::vector<FishData> getDataFromFish(std::vector<Fish> &fish) {
  std::vector<FishData> data;
  data.reserve(fish.size());
  for (Fish &f : fish) {
    data.emplace_back(f.getData());
  }
  return data;
}

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

  std::vector<Fish> fishs(50);

  // ImGui demo
  std::string text = "Hello";

  ctx.imgui = [&]() {
    ImGui::Begin("Parameters");
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Boid parameters");
    ImGui::SliderFloat("Visual range", &Config::getInstance().VISUAL_RANGE, 0.f,
                       0.2f);
    ImGui::SliderFloat("Vital space", &Config::getInstance().MIN_DISTANCE, 0.f,
                       0.1f);
    ImGui::SliderFloat("Speed limit", &Config::getInstance().SPEED_LIMIT, 0.f,
                       0.01f);
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Behavior parameters");
    ImGui::SliderFloat("Separation", &Config::getInstance().SEPARATION_FACTOR,
                       0.f, 0.01f);
    ImGui::SliderFloat("Alignment", &Config::getInstance().ALIGNMENT_FACTOR,
                       0.f, 0.1f);
    ImGui::SliderFloat("Cohesion", &Config::getInstance().COHESION_FACTOR, 0.f,
                       0.01f);
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Wall avoidance parameters");
    ImGui::SliderFloat("Wall margin", &Config::getInstance().WALL_MARGIN, 0.f,
                       0.2f);
    ImGui::SliderFloat("Wall turn", &Config::getInstance().WALL_TURN_FACTOR,
                       0.f, 0.05f);
    ImGui::End();
    // Show the official ImGui demo window
    // It is very useful to discover all the widgets available in ImGui
    ImGui::ShowDemoWindow();
  };

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    std::vector<FishData> fishData = getDataFromFish(fishs);

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
