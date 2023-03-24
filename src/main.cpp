#include "Behavior.hpp"
#include "Config.hpp"
#include "Environment.hpp"
#include "Fish.hpp"
#include "Food.hpp"
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

void eatingTime(std::vector<Fish> &fishs, std::vector<Food> &foods) {
  for (Fish &fish : fishs) {
    for (Food &food : foods) {
      if (glm::distance(food.getPosition(), fish.getData()._center) <
          food.getHitbox()) {
        fish.eats(food);
        if (!fish.canEat()) {
          break;
        }
      }
    }
  }
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

  std::vector<Fish> fishs = std::vector<Fish>(200);

  ctx.imgui = [&]() {
    ImGui::Begin("Parameters");

    if (ImGui::CollapsingHeader("Boid parameters")) {
      ImGui::SliderFloat("Visual range", &Config::getInstance().VISUAL_RANGE,
                         0.f, 0.3f);
      ImGui::SliderFloat("Vital space", &Config::getInstance().MIN_DISTANCE,
                         0.f, 0.1f);
      ImGui::SliderFloat("Speed limit", &Config::getInstance().SPEED_LIMIT, 0.f,
                         0.01f);
    }

    if (ImGui::CollapsingHeader("Behavior parameters")) {
      ImGui::SliderFloat("Separation", &Config::getInstance().SEPARATION_FACTOR,
                         0.f, 0.01f);
      ImGui::SliderFloat("Alignment", &Config::getInstance().ALIGNMENT_FACTOR,
                         0.f, 0.1f);
      ImGui::SliderFloat("Cohesion", &Config::getInstance().COHESION_FACTOR,
                         0.f, 0.005f);
    }

    if (ImGui::CollapsingHeader("Wall avoidance parameters")) {
      ImGui::SliderFloat("Wall margin", &Config::getInstance().WALL_MARGIN, 0.f,
                         0.2f);
      ImGui::SliderFloat("Wall turn", &Config::getInstance().WALL_TURN_FACTOR,
                         0.f, 0.05f);
    }

    if (ImGui::CollapsingHeader("Debug")) {
      ImGui::Checkbox("Show visual ranges",
                      &Config::getInstance().SHOW_VISUAL_RANGES);
      ImGui::Checkbox("Show movement vector",
                      &Config::getInstance().SHOW_MOVEMENT_VECTOR);
    }

    if (ImGui::CollapsingHeader("Colors")) {
      static bool alpha_preview = true;
      static bool alpha_half_preview = false;
      static bool drag_and_drop = true;
      static bool options_menu = true;
      static bool hdr = false;
      ImGuiColorEditFlags misc_flags =
          (hdr ? ImGuiColorEditFlags_HDR : 0) |
          (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) |
          (alpha_half_preview
               ? ImGuiColorEditFlags_AlphaPreviewHalf
               : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) |
          (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

      ImGui::ColorEdit4("Fish type #1",
                        Config::getInstance().FISH_COLOR_1.data(), misc_flags);

      ImGui::ColorEdit4("Food", Config::getInstance().FOOD_COLOR.data(),
                        misc_flags);
      ImGui::ColorEdit4("Food - Fill",
                        Config::getInstance().FOOD_FILL_COLOR.data(),
                        misc_flags);
      ImGui::ColorEdit4("Visual range",
                        Config::getInstance().VISUAL_RANGE_COLOR.data(),
                        misc_flags);
      ImGui::ColorEdit4("Visual range - Fill",
                        Config::getInstance().VISUAL_RANGE_FILL_COLOR.data(),
                        misc_flags);
      ImGui::ColorEdit4("Movement range",
                        Config::getInstance().MOVEMENT_RANGE_COLOR.data(),
                        misc_flags);
    }
    ImGui::End();

    // Show the official ImGui demo window
    // It is very useful to discover all the widgets available in ImGui
    // ImGui::ShowDemoWindow();
  };

  ctx.mouse_pressed = [&](p6::MouseButton button) {
    if (button.button == p6::Button::Left) {
      Environment::getInstance().foods.emplace_back(
          Food({button.position.x, button.position.y, 0}));
    }
  };

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    Environment::getInstance().fishData = getDataFromFish(fishs);

    // Comparison square
    // ctx.square(p6::Center{0, 0}, p6::Radius{1});

    for (Fish &fish : fishs) {
      fish.draw(ctx);
      fish.update();
      fish.applyBehaviors(Environment::getInstance());
    }

    eatingTime(fishs, Environment::getInstance().foods);

    // Food
    std::vector<Food> tmp;

    for (Food &food : Environment::getInstance().foods) {
      if (food.exists()) {
        tmp.emplace_back(food);
        food.draw(ctx);
      }
    }

    Environment::getInstance().foods = tmp;
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}
