#include "Camera/FreeflyCamera.hpp"
#include "Config.hpp"
#include "Elements/Behavior.hpp"
#include "Elements/Environment.hpp"
#include "Elements/Fish/Fish.hpp"
#include "Elements/Fish/FishData.hpp"
#include "Elements/Food/Food.hpp"
#include "Elements/Obstacle/Obstacle.hpp"
#include "Elements/Positionable.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "internal/geometry.hpp"
#include "internal/imgui.hpp"
#include "internal/stream.hpp"

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
      if (food->exists() && isNear(*food, *fish, food->getRadius())) {
        fish->eats(food);
        if (!fish->canEat()) {
          break;
        }
      }
    }
  }
}

template <typename T> std::vector<std::shared_ptr<T>> generate(int count) {
  std::vector<std::shared_ptr<T>> vec;
  vec.reserve(count);

  for (int i = 0; i < count; i++) {
    vec.emplace_back(std::make_shared<T>());
  }

  return vec;
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
  Config::get().ASPECT_RATIO = ctx.aspect_ratio();

  auto fishs = generate<Fish>(Config::get().FISH_COUNT);
  Environment::getInstance().obstacles.elements =
      generate<Obstacle>(Config::get().OBSTACLE_COUNT);

  ctx.imgui = [&]() { imguiInit(); };

  ctx.mouse_pressed = [&](p6::MouseButton button) {
    if (button.button == p6::Button::Right) {
      Environment::getInstance().foods.elements.emplace_back(
          std::make_shared<Food>(
              glm::vec3{button.position.x, button.position.y, 0}));
    }
  };

  FreeflyCamera camera;

  ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
    camera.rotateLeft(scroll.dy);
    camera.rotateUp(scroll.dx);
  };

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    Environment::getInstance().fishData.elements = getDataFromFish(fishs);

    // -- Debug -- Border rectangle
    // ctx.rectangle(p6::TopLeftCorner{-Config::get().ASPECT_RATIO, 1},
    //              p6::Radii{2 * Config::get().ASPECT_RATIO, 2});

    for (auto &fish : fishs) {
      fish->update();
      fish->draw(ctx);
    }

    for (const auto &obstacle :
         Environment::getInstance().obstacles.getElements()) {
      obstacle->draw(ctx);
    }

    eatingTime(fishs, Environment::getInstance().foods.elements);

    // -- Debug -- Check food HP
    // for (auto food : Environment::getInstance().foods) {
    //   std::cout << "Food HP: " << food->getRemainingBites() << '\n';
    // }

    // Food

    Environment::getInstance().foods.elements =
        filter(Environment::getInstance().foods.elements,
               Predicate<std::shared_ptr<Food>>(
                   [](std::shared_ptr<Food> &f) { return f->exists(); }));

    for (auto &food : Environment::getInstance().foods) {
      if (food->exists()) {
        food->draw(ctx);
      }
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}
