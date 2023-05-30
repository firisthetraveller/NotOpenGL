#include "ShaderManager.hpp"
#include <string>
#include <utility>
#include "Config.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

ShaderManager::ShaderManager(const std::string &vertexShaderPath,
                             const std::string &fragmentShaderPath)
    : program{p6::load_shader(vertexShaderPath, fragmentShaderPath)},
      uMVPMatrix(glGetUniformLocation(program.id(), "uMVPMatrix")),
      uModelMatrix(glGetUniformLocation(program.id(), "uModelMatrix")),
      uNormalMatrix(glGetUniformLocation(program.id(), "uNormalMatrix")) {}

bool ShaderManager::addUniformTexture(const std::string& texturePath, const std::string& uniformString, GLuint texture) {
  GLint uniform = glGetUniformLocation(program.id(), uniformString.data());
  _textureUniforms.emplace(texturePath, std::make_pair(uniform, texture));
  return !(uniform == -1);
}

void ShaderManager::setUniformTexture() const {
  int index = 0;
  for (const auto& [name, textureData] : _textureUniforms) {
    glUniform1i(textureData.first, index++);
  }
}

void ShaderManager::enableActiveTextures() const {
  int index = 0;
  for (const auto& [name, textureData] : _textureUniforms) {
    glActiveTexture(GL_TEXTURE0 + index++);
    glBindTexture(GL_TEXTURE_2D, textureData.second);
  }
}

void ShaderManager::disableActiveTextures() const {
  for (unsigned int index = 0; index < _textureUniforms.size(); index++) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}

void ShaderManager::setUniformMatrix(glm::mat4& MVPMatrix, glm::mat4& MVMatrix, glm::mat4& NormalMatrix) const {
  glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
  glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
}
