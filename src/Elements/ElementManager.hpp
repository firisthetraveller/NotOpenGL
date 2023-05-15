#ifndef __ELEMENTMANAGER__
#define __ELEMENTMANAGER__

#include "Config.hpp"
#include "Elements/Positionable.hpp"
#include "OpenGL/ShaderManager.hpp"
#include "glimac/common.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include <memory>
#include <p6/p6.h>
#include <string>
#include <vector>

template <is_positionable Element> class ElementManager {
private:
  GLuint _vao{};
  std::unique_ptr<ShaderManager> _shader;
  std::vector<glimac::ShapeVertex> _vertices;

public:
  std::vector<std::shared_ptr<Element>> elements;

  /**
   * @param texturePath : Path to the file on the disk drive.
   */
  ElementManager();
  void setElementVertices(std::vector<glimac::ShapeVertex> &vertices);
  void setShaderManager(std::unique_ptr<ShaderManager> &shader);
  void draw(glm::mat4 &viewMatrix) const;
  auto getElements() const { return elements; };
  auto begin() { return elements.begin(); };
  auto end() { return elements.end(); };
};

template <is_positionable Element> ElementManager<Element>::ElementManager() {
  glGenVertexArrays(1, &_vao);
}

template <is_positionable Element>
void ElementManager<Element>::setElementVertices(
    std::vector<glimac::ShapeVertex> &vertices) {
  _vertices = vertices;
}

template <is_positionable Element>
void ElementManager<Element>::setShaderManager(
    std::unique_ptr<ShaderManager> &shader) {
  _shader = shader;
}

template <is_positionable Element>
void ElementManager<Element>::draw(glm::mat4 &viewMatrix) const {
  glBindVertexArray(_vao);
  {
    _shader->use();

    // glUniforms
    _shader->setUniformTexture();

    // glBindTexture
    _shader->enableActiveTextures();

    // Matrix shit
    for (auto &element : elements) {
      static glm::mat4 projMatrix = glm::perspective(
          glm::radians(70.f), Config::get().ASPECT_RATIO, 0.1f, 100.f);
      glm::mat4 modelMatrix = getModelMatrix(*element);
      glm::mat4 MVPMatrix = projMatrix * viewMatrix * modelMatrix;
      glm::mat4 MVMatrix = viewMatrix * modelMatrix;
      glm::mat4 NormalMatrix = glm::transpose(glm::inverse(modelMatrix));

      // glUniformMatrix
      _shader->setUniformMatrix(MVPMatrix, MVMatrix, NormalMatrix);

      // glDrawArrays
      glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    }

    _shader->disableActiveTextures();
  }
  glBindVertexArray(0);
}

#endif
