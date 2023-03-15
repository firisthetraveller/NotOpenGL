#ifndef __FISH_CONFIG__
#define __FISH_CONFIG__

struct Config {
private:
  Config() = default;

public:
  Config(Config &other) = delete;
  Config(Config &&move) = delete;

  float MIN_DISTANCE = 0.02f;
  float VISUAL_RANGE = 0.5f;
  float ASPECT_RATIO = 1.0f;

  float COHESION_FACTOR = 0.005f;
  float ALIGNMENT_FACTOR = 0.005f;
  float SEPARATION_FACTOR = 0.005f;

  static Config &getInstance() {
    static Config INSTANCE;

    return INSTANCE;
  }
};

#endif
