#include "Elements/Environment.hpp"

Environment &Environment::build() {
  fishData.setElementVertices(glimac::sphere_vertices(1.f, 32, 16));
  std::shared_ptr<ShaderManager> fishShader = std::make_shared<ShaderManager>(
      "shaders/3D.vs.glsl", "shaders/multiTex3D.fs.glsl");
  GLuint earthLocation =
      TextureManager::getInstance().loadTexture("assets/textures/EarthMap.jpg");
  fishShader->addUniformTexture("assets/textures/EarthMap.jpg", "uTexture1",
                                earthLocation);

  GLuint cloudLocation =
      TextureManager::getInstance().loadTexture("assets/textures/CloudMap.jpg");
  fishShader->addUniformTexture("assets/textures/CloudMap.jpg", "uTexture2",
                                cloudLocation);
  fishData.setShaderManager(fishShader);

  obstacles.setElementVertices(glimac::sphere_vertices(1.f, 32, 16));
  std::shared_ptr<ShaderManager> obstaclesShader =
      std::make_shared<ShaderManager>("shaders/3D.vs.glsl",
                                      "shaders/tex3D.fs.glsl");
  GLuint moonLocation =
      TextureManager::getInstance().loadTexture("assets/textures/MoonMap.jpg");
  obstaclesShader->addUniformTexture("assets/textures/MoonMap.jpg", "uTexture1",
                                     moonLocation);
  obstacles.setShaderManager(obstaclesShader);

  foods.setElementVertices(glimac::sphere_vertices(1.f, 32, 16));
  foods.setShaderManager(obstaclesShader);

  return *this;
}
