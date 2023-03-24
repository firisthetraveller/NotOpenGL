#ifndef __FISH_CONFIG__
#define __FISH_CONFIG__

#include "imgui.h"
#include <array>
struct Config {
private:
  Config() = default;

public:
  Config(Config &other) = delete;
  Config(Config &&move) = delete;
  float MIN_DISTANCE = 0.05f;
  float VISUAL_RANGE = 0.15f;
  float ASPECT_RATIO = 1.0f;

  // Behavior
  float COHESION_FACTOR = 0.001f;
  float ALIGNMENT_FACTOR = 0.05f;
  float SEPARATION_FACTOR = 0.005f;

  float SPEED_LIMIT = 0.002f;

  // Wall detection
  float WALL_MARGIN = 0.1f;
  float WALL_TURN_FACTOR = 0.005f;

  // Food
  float DEFAULT_FOOD_SIZE = 0.01f;
  int DEFAULT_FOOD_BITES = 10;

  // Visual indicators
  bool SHOW_VISUAL_RANGES = true;
  bool SHOW_MOVEMENT_VECTOR = true;

  // Style
  std::array<float, 4> FISH_COLOR_1 = {0.f, 0.f, 0.f, 200.0f / 255.0f};
  std::array<float, 4> VISUAL_RANGE_COLOR = {0.f, 0.f, 0.f, 200.0f / 255.0f};
  std::array<float, 4> VISUAL_RANGE_FILL_COLOR = {
      114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f};
  std::array<float, 4> MOVEMENT_RANGE_COLOR = {0.f, 0.f, 0.f, 200.0f / 255.0f};

  static Config &getInstance() {
    static Config INSTANCE;

    return INSTANCE;
  }
};

#endif
