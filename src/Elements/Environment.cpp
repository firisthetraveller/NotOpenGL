#include "Elements/Environment.hpp"
#include <vector>
#include "Elements/ElementManager.hpp"
#include "Elements/Fish/FishData.hpp"
#include "Elements/Obstacle/Obstacle.hpp"
#include "Lights/DirectionalLight.hpp"
#include "OpenGL/ShaderManager.hpp"
#include "OpenGL/TextureManager.hpp"
#include "glimac/cone_vertices.hpp"
#include "glimac/sphere_vertices.hpp"

static std::vector<DirectionalLight> buildLights() {
  std::vector<DirectionalLight> lights;

  lights.push_back(
    DirectionalLight{
      {1, 1, 1, 0},
      {2, 2, 1.5},
      {1, -1, -1}}
  );
  lights.push_back(
    DirectionalLight{
      {-1, -1, -1, 0},
      {0.4, 0.4, 0.8},
      {1, -1, -1}}
  );

  return lights;
}

static ElementManager<FishData> buildFish() {
  ElementManager<FishData> fishElements;

  fishElements.setElementVertices(glimac::cone_lowLOD(), glimac::cone_highLOD());
  std::shared_ptr<ShaderManager> fishShader = std::make_shared<ShaderManager>(
    "shaders/3D.vs.glsl", "shaders/multiTexLights.fs.glsl"
  );
  GLuint earthLocation =
    TextureManager::getInstance().loadTexture("assets/textures/EarthMap.jpg");
  fishShader->addUniformTexture("assets/textures/EarthMap.jpg", "uTexture1", earthLocation);

  // GLuint cloudLocation =
  //   TextureManager::getInstance().loadTexture("assets/textures/CloudMap.jpg");
  // fishShader->addUniformTexture("assets/textures/CloudMap.jpg", "uTexture2", cloudLocation);

  fishElements.setShaderManager(fishShader);

  return fishElements;
}

static ElementManager<Obstacle> buildObstacles() {
  ElementManager<Obstacle> obstacleElements;

  obstacleElements.setElementVertices(glimac::sphere_lowLOD(), glimac::sphere_highLOD());
  std::shared_ptr<ShaderManager> obstaclesShader =
    std::make_shared<ShaderManager>("shaders/3D.vs.glsl", "shaders/multiTexLights.fs.glsl");
  GLuint moonLocation =
    TextureManager::getInstance().loadTexture("assets/textures/MoonMap.jpg");
  obstaclesShader->addUniformTexture("assets/textures/MoonMap.jpg", "uTexture1", moonLocation);
  obstacleElements.setShaderManager(obstaclesShader);

  return obstacleElements;
}

static ElementManager<Food> buildFoods() {
  ElementManager<Food> foods;

  foods.setElementVertices(glimac::sphere_lowLOD(), glimac::sphere_highLOD());
  std::shared_ptr<ShaderManager> foodShader =
    std::make_shared<ShaderManager>("shaders/3D.vs.glsl", "shaders/multiTexLights.fs.glsl");
  GLuint moonLocation =
    TextureManager::getInstance().loadTexture("assets/textures/MoonMap.jpg");
  foodShader->addUniformTexture("assets/textures/MoonMap.jpg", "uTexture1", moonLocation);
  foods.setShaderManager(foodShader);

  return foods;
}

Environment& Environment::build() {
  lights    = buildLights();
  fishData  = buildFish();
  obstacles = buildObstacles();
  foods     = buildFoods();

  return *this;
}
