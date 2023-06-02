#include "Elements/Environment.hpp"
#include <string>
#include <vector>
#include "Elements/Boundary.hpp"
#include "Elements/ElementManager.hpp"
#include "Elements/Fish/FishData.hpp"
#include "Elements/Obstacle/Obstacle.hpp"
#include "Elements/Positionable.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Materials/Material.hpp"
#include "OpenGL/ShaderManager.hpp"
#include "OpenGL/TextureManager.hpp"
#include "glimac/common.hpp"
#include "glimac/cone_vertices.hpp"
#include "glimac/cube_vertices.hpp"
#include "glimac/sphere_vertices.hpp"

template<is_positionable Element>
static ElementManager<Element> buildElements(
  const std::vector<glimac::ShapeVertex>& lowLOD,
  const std::vector<glimac::ShapeVertex>& highLOD,
  const Material&                         material,
  const std::string&                      vertexShaderPath,
  const std::string&                      fragmentShaderPath,
  const std::string&                      texturePath
) {
  ElementManager<Element> elements;

  elements.setElementVertices(lowLOD, highLOD);
  elements.setMaterial(material);
  std::shared_ptr<ShaderManager> fishShader = std::make_shared<ShaderManager>(
    vertexShaderPath, fragmentShaderPath
  );
  GLuint location =
    TextureManager::getInstance().loadTexture(texturePath);
  fishShader->addUniformTexture(texturePath, "uTexture1", location);

  elements.setShaderManager(fishShader);

  return elements;
}

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
  return buildElements<FishData>(
    glimac::cone_lowLOD(),
    glimac::cone_highLOD(),
    Material{glm::vec3(0.61568, 0.61424, 0.62568), glm::vec3(0.633, 0.727811, 0.633), 32.f},
    "shaders/3D.vs.glsl",
    "shaders/multiTexLights.fs.glsl",
    "assets/textures/EarthMap.jpg"
  );
}

static ElementManager<Obstacle> buildObstacles() {
  return buildElements<Obstacle>(
    glimac::sphere_lowLOD(),
    glimac::sphere_highLOD(),
    Material{glm::vec3(0.61568, 0.61424, 0.62568), glm::vec3(0.633, 0.727811, 0.633), 32.f},
    "shaders/3D.vs.glsl",
    "shaders/multiTexLights.fs.glsl",
    "assets/textures/MoonMap.jpg"
  );
}

static ElementManager<Food> buildFoods() {
  return buildElements<Food>(
    glimac::sphere_lowLOD(),
    glimac::sphere_highLOD(),
    Material{glm::vec3(0.61568, 0.61424, 0.62568), glm::vec3(0.633, 0.727811, 0.633), 32.f},
    "shaders/3D.vs.glsl",
    "shaders/multiTexLights.fs.glsl",
    "assets/textures/MoonMap.jpg"
  );
}

static ElementManager<Boundary> buildBoundary() {
  ElementManager<Boundary> boundary = buildElements<Boundary>(
    glimac::cube_vertices(),
    glimac::cube_vertices(),
    Material{glm::vec3(0.61568, 0.61424, 0.62568), glm::vec3(0.633, 0.727811, 0.633), 32.f},
    "shaders/3D.vs.glsl",
    "shaders/multiTexLights.fs.glsl",
    "assets/textures/quarry_04_puresky_1k.png"
  );

  boundary.elements.emplace_back(std::make_shared<Boundary>());

  return boundary;
}

Environment& Environment::build() {
  lights    = buildLights();
  fishData  = buildFish();
  obstacles = buildObstacles();
  foods     = buildFoods();
  boundary  = buildBoundary();

  return *this;
}
