#ifndef __ENVIRONMENT_FISH__
#define __ENVIRONMENT_FISH__

#include "Elements/ElementManager.hpp"
#include "Elements/Fish/FishData.hpp"
#include "Elements/Food/Food.hpp"
#include "Elements/Obstacle/Obstacle.hpp"
#include "OpenGL/ShaderManager.hpp"
#include "OpenGL/TextureManager.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/gtx/string_cast.hpp"

#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

struct Environment {
private:
  Environment() = default;
  Environment(Environment &other) = default;
  Environment(Environment &&move) = default;
  Environment &build();

public:
  ElementManager<FishData> fishData;
  ElementManager<Food> foods;
  ElementManager<Obstacle> obstacles;

  static void draw(const glm::mat4 &viewMatrix) {
    // std::cout << "View matrix: " << glm::to_string(viewMatrix) << std::endl;
    getInstance().fishData.draw(viewMatrix);

    // getInstance().foods.draw(viewMatrix);
    getInstance().obstacles.draw(viewMatrix);
  }

  static Environment &getInstance() {
    static Environment INSTANCE = Environment().build();
    return INSTANCE;
  }
};

#endif
