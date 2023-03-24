#ifndef __FISH_CONFIG__
#define __FISH_CONFIG__

struct Config {
private:
  Config() = default;

public:
  Config(Config &other) = delete;
  Config(Config &&move) = delete;
  float MIN_DISTANCE = 0.05f;
  float VISUAL_RANGE = 0.1f;
  float ASPECT_RATIO = 1.0f;

  // Behavior
  float COHESION_FACTOR = 0.005f;
  float ALIGNMENT_FACTOR = 0.005f;
  float SEPARATION_FACTOR = 0.005f;

  float SPEED_LIMIT = 0.002f;

  // Wall detection
  float WALL_MARGIN = 0.1f;
  float WALL_TURN_FACTOR = 0.005f;

  // Food
  float DEFAULT_FOOD_SIZE = 0.01f;
  int DEFAULT_FOOD_BITES = 10;

  static Config &getInstance() {
    static Config INSTANCE;

    return INSTANCE;
  }
};

#endif
