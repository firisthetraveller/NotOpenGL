#ifndef __ENVIRONMENT_FISH__
#define __ENVIRONMENT_FISH__

#include "Elements/Boundary.hpp"
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
  ElementManager<Boundary>      boundary;

  void draw(const glm::vec3 cameraPos, const glm::mat4& viewMatrix, float appTime) const {
    // std::cout << "View matrix: " << glm::to_string(viewMatrix) << std::endl;
    fishData.draw(cameraPos, viewMatrix, lights, appTime);
    foods.draw(cameraPos, viewMatrix, lights, appTime);
    obstacles.draw(cameraPos, viewMatrix, lights, appTime);
    boundary.draw(cameraPos, viewMatrix, lights, appTime);
  }

  static Environment& getInstance() {
    static Environment INSTANCE = Environment().build();
    return INSTANCE;
  }
};

#endif
