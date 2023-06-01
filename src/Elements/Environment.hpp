#ifndef __ENVIRONMENT_FISH__
#define __ENVIRONMENT_FISH__

#include "Elements/ElementManager.hpp"
#include "Elements/Fish/FishData.hpp"
#include "Elements/Food/Food.hpp"
#include "Elements/Obstacle/Obstacle.hpp"
#include "Lights/DirectionalLight.hpp"
#include "glm/ext/vector_float3.hpp"
// #include "glm/gtx/string_cast.hpp"

#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

struct Environment {
  private:
  Environment()                   = default;
  Environment(Environment& other) = default;
  Environment(Environment&& move) = default;
  Environment& build();

  public:
  std::vector<DirectionalLight> lights;
  ElementManager<FishData>      fishData;
  ElementManager<Food>          foods;
  ElementManager<Obstacle>      obstacles;

  static void draw(const glm::vec3 cameraPos, const glm::mat4& viewMatrix) {
    // std::cout << "View matrix: " << glm::to_string(viewMatrix) << std::endl;
    getInstance().fishData.draw(cameraPos, viewMatrix);
    getInstance().foods.draw(cameraPos, viewMatrix);
    getInstance().obstacles.draw(cameraPos, viewMatrix);
  }

  static Environment& getInstance() {
    static Environment INSTANCE = Environment().build();
    return INSTANCE;
  }
};

#endif
