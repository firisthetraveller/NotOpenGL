#ifndef __SHADERMANAGER__
#define __SHADERMANAGER__

#include <map>
#include <p6/p6.h>
#include <string>
#include <utility>
#include <vector>

#include "TextureData.hpp"

class ShaderManager {
private:
  p6::Shader program;
  std::map<std::string, TextureData> _textureUniforms;

  GLint uMVPMatrix;
  GLint uModelMatrix;
  GLint uNormalMatrix;

public:
  ShaderManager(const std::string &vertexShaderPath,
                const std::string &fragmentShaderPath);

  void use() { program.use(); }

  /**
   * Builder method for ShaderManager.
   * Adds a key/value in a texture map with:
   * - key: path of the texture
   * - value: uniformString & textureLocation
   */
  bool addUniformTexture(const std::string &texturePath,
                         const std::string &uniformString, GLuint texture);

  /**
   * Set all the texture related uniforms.
   * @warning If you have texture uniforms, don't forget to set them with
   * `addUniformTexture`!
   */
  void setUniformTexture() const;
  void enableActiveTextures() const;
  void disableActiveTextures() const;
  void setUniformMatrix(glm::mat4 &MVPMatrix, glm::mat4 &MVMatrix,
                        glm::mat4 &NormalMatrix) const;
};

#endif
