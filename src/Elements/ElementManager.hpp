#ifndef __ELEMENTMANAGER__
#define __ELEMENTMANAGER__

#include <p6/p6.h>
#include <memory>
#include <string>
#include <vector>
#include "Config.hpp"
#include "Elements/Positionable.hpp"
#include "OpenGL/ShaderManager.hpp"
#include "glimac/common.hpp"
#include "glm/ext/matrix_float4x4.hpp"

template<is_positionable Element>
class ElementManager {
  private:
  GLuint                           _vao{};
  std::shared_ptr<ShaderManager>   _shader;
  std::vector<glimac::ShapeVertex> _vertices;

  public:
  std::vector<std::shared_ptr<Element>> elements;

  /**
   * @param texturePath : Path to the file on the disk drive.
   */
  ElementManager();
  void setElementVertices(const std::vector<glimac::ShapeVertex>& vertices);
  void setShaderManager(const std::shared_ptr<ShaderManager>& shader);
  void draw(const glm::mat4& viewMatrix) const;
  auto getElements() const { return elements; };
  auto begin() { return elements.begin(); };
  auto end() { return elements.end(); };
};

template<is_positionable Element>
ElementManager<Element>::ElementManager() {
  glGenVertexArrays(1, &_vao);
}

template<is_positionable Element>
void ElementManager<Element>::setElementVertices(
  const std::vector<glimac::ShapeVertex>& vertices
) {
  _vertices = vertices;

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  {
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(_vao);
  {
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    const GLuint VERTEX_ATTR_UV_COORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_UV_COORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    {
      // Attribute | Size | Variable size | ? | Size of one vertex complete data
      // | Offset
      glVertexAttribPointer(
        VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
        sizeof(glimac::ShapeVertex),
        (const void*)(offsetof(glimac::ShapeVertex, position))
      );
      glVertexAttribPointer(
        VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
        sizeof(glimac::ShapeVertex),
        (const void*)(offsetof(glimac::ShapeVertex, normal))
      );
      glVertexAttribPointer(
        VERTEX_ATTR_UV_COORDS, 2, GL_FLOAT, GL_FALSE,
        sizeof(glimac::ShapeVertex),
        (const void*)(offsetof(glimac::ShapeVertex, texCoords))
      );
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
}

template<is_positionable Element>
void ElementManager<Element>::setShaderManager(
  const std::shared_ptr<ShaderManager>& shader
) {
  _shader = shader;
}

template<is_positionable Element>
void ElementManager<Element>::draw(const glm::mat4& viewMatrix) const {
  glBindVertexArray(_vao);
  {
    _shader->use();

    // glUniforms
    _shader->setUniformTexture();

    // glBindTexture
    _shader->enableActiveTextures();

    // Matrix shit
    for (auto& element : elements) {
      static glm::mat4 projMatrix = glm::perspective(
        glm::radians(70.f), Config::get().ASPECT_RATIO, 0.1f, 100.f
      );
      glm::mat4 modelMatrix  = getModelMatrix(*element);
      glm::mat4 MVPMatrix    = projMatrix * viewMatrix * modelMatrix;
      glm::mat4 MVMatrix     = viewMatrix * modelMatrix;
      glm::mat4 NormalMatrix = glm::transpose(glm::inverse(modelMatrix));

      // glUniformMatrix
      _shader->setUniformMatrix(MVPMatrix, MVMatrix, NormalMatrix);

      // glDrawArrays
      glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertices.size()));
    }

    _shader->disableActiveTextures();
  }
  glBindVertexArray(0);
}

#endif
