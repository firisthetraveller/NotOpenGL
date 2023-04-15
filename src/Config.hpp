#ifndef __FISH_CONFIG__
#define __FISH_CONFIG__

#include "imgui.h"
#include "internal/graphics.hpp"

struct Config {
private:
  Config() = default;

public:
  Config(Config &other) = delete;
  Config(Config &&move) = delete;

  // Simulation parameters
  int FISH_COUNT = 100;
  int OBSTACLE_COUNT = 5;
  int HISTORY_SIZE = 100;

  float SEPARATION_MIN_DISTANCE = 0.02f;
  float VISUAL_RANGE = 0.2f;
  float ASPECT_RATIO = 1.0f;

  // Behavior
  float COHESION_FACTOR = 0.001f;
  float ALIGNMENT_FACTOR = 0.05f;
  float SEPARATION_FACTOR = 0.025f;
  float OBSTACLE_AVOIDANCE_FACTOR = 0.04f;

  float OBSTACLE_DETECTION_RADIUS = 0.25f;

  float SPEED_LIMIT = 0.005f;

  // Wall detection
  float WALL_MARGIN = 0.2f;
  float WALL_TURN_FACTOR = 0.001f;

  // Food
  float DEFAULT_FOOD_SIZE = 0.01f;
  int DEFAULT_FOOD_BITES = 10;
  int FOOD_COOLDOWN_FRAMES = 60;

  // Visual indicators
  bool SHOW_VISUAL_RANGES = false;
  bool SHOW_MOVEMENT_VECTOR = false;
  bool SHOW_POSITION_HISTORY = false;

  // Style
  Graphics::Color FISH_1_COLOR = Graphics::NamedColor::NONE;
  Graphics::Color FISH_1_FILL_COLOR = Graphics::NamedColor::BLACK;

  Graphics::Color FOOD_COLOR = Graphics::NamedColor::NONE;
  Graphics::Color FOOD_FILL_COLOR = Graphics::NamedColor::RED;

  Graphics::Color OBSTACLE_STROKE_COLOR = Graphics::NamedColor::BLACK;
  Graphics::Color OBSTACLE_FILL_COLOR = {0.5f, 0.5f, 0.5f, 255.0f / 255.0f};

  Graphics::Color VISUAL_RANGE_COLOR = Graphics::NamedColor::BLACK;
  Graphics::Color VISUAL_RANGE_FILL_COLOR = {114.0f / 255.0f, 144.0f / 255.0f,
                                             154.0f / 255.0f, 20.0f / 255.0f};

  Graphics::Color MOVEMENT_RANGE_COLOR = Graphics::NamedColor::BLACK;
  Graphics::Color MOVEMENT_HISTORY_COLOR = Graphics::NamedColor::WHITE;

  static Config &get() {
    static Config INSTANCE;

    return INSTANCE;
  }
};

#endif
