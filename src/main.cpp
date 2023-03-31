#include "Behavior.hpp"
#include "Config.hpp"
#include "Environment.hpp"
#include "Fish/Fish.hpp"
#include "Fish/FishData.hpp"
#include "Food/Food.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "internal/stream.hpp"
#include "p6/p6.h"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "internal/imgui.hpp"

static std::vector<std::shared_ptr<FishData>>
getDataFromFish(std::vector<std::shared_ptr<Fish>> &fishs) {
  std::vector<std::shared_ptr<FishData>> data;
  data.reserve(fishs.size());

  for (auto &fish : fishs) {
    data.emplace_back(fish->getData());
  }

  return data;
}

static void eatingTime(std::vector<std::shared_ptr<Fish>> &fishs,
                       std::vector<std::shared_ptr<Food>> &foods) {
  for (auto &fish : fishs) {
    if (!fish->canEat()) {
      continue;
    }

    for (auto &food : foods) {
      if (food->exists() &&
          glm::distance(food->getPosition(), fish->getData()->_center) <
              food->getHitbox()) {
        fish->eats(food);
        if (!fish->canEat()) {
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
  auto ctx = p6::Context{{.title = "NotOpenGL"}};
  ctx.maximize_window();
  Config::getInstance().ASPECT_RATIO = ctx.aspect_ratio();

  std::vector<std::shared_ptr<Fish>> fishs;
  fishs.reserve(30);

  for (int i = 0; i < 10; i++) {
    fishs.emplace_back(std::make_shared<Fish>());
  }

  ctx.imgui = [&]() { imguiInit(); };

  ctx.mouse_pressed = [&](p6::MouseButton button) {
    if (button.button == p6::Button::Right) {
      Environment::getInstance().foods.emplace_back(std::make_shared<Food>(
          glm::vec3{button.position.x, button.position.y, 0}));
    }
  };

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    Environment::getInstance().fishData = getDataFromFish(fishs);

    // Border rectangle
    // ctx.rectangle(p6::TopLeftCorner{-Config::getInstance().ASPECT_RATIO, 1},
    //              p6::Radii{2 * Config::getInstance().ASPECT_RATIO, 2});

    for (auto &fish : fishs) {
      fish->applyBehaviors(Environment::getInstance());
      fish->update();
      fish->draw(ctx);
    }

    eatingTime(fishs, Environment::getInstance().foods);

    // Food
    Environment::getInstance().foods =
        filter(Environment::getInstance().foods,
               Predicate<std::shared_ptr<Food>>(
                   [](std::shared_ptr<Food> &f) { return f->exists(); }));

    std::cout << "remaining food : " << Environment::getInstance().foods.size()
              << '\n';

    for (auto &food : Environment::getInstance().foods) {
      if (food->exists()) {
        food->draw(ctx);
      }
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}
