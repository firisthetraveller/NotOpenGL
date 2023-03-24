#include "Behavior.hpp"
#include "Config.hpp"
#include "Environment.hpp"
#include "Fish/Fish.hpp"
#include "Food/Food.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
#include <cstdlib>
#include <memory>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "internal/imgui.hpp"

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

  ctx.imgui = [&]() { imguiInit(); };

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
