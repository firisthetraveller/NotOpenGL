#ifndef __ELEMENTMANAGER__
#define __ELEMENTMANAGER__

#include <p6/p6.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Config.hpp"
#include "Elements/Positionable.hpp"
#include "OpenGL/ShaderManager.hpp"
#include "glimac/common.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/geometric.hpp"

template<is_positionable Element>
class ElementManager {
  private:
  GLuint                           _vao{};
  std::shared_ptr<ShaderManager>   _shader;
  std::vector<glimac::ShapeVertex> _vertices;
  std::vector<unsigned int>        vertexCountLOD;

  public:
  std::vector<std::shared_ptr<Element>> elements;

  /**
   * @param texturePath : Path to the file on the disk drive.
   */
  ElementManager();
  void setElementVertices(const std::vector<glimac::ShapeVertex>& verticesLowLOD, const std::vector<glimac::ShapeVertex>& verticesHighLOD);
  void setShaderManager(const std::shared_ptr<ShaderManager>& shader);
  void draw(const glm::vec3& cameraPos, const glm::mat4& viewMatrix) const;
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
  const std::vector<glimac::ShapeVertex>& verticesLowLOD, const std::vector<glimac::ShapeVertex>& verticesHighLOD
) {
  for (const auto& vertex : verticesLowLOD) {
    _vertices.emplace_back(vertex);
  }

  for (const auto& vertex : verticesHighLOD) {
    _vertices.emplace_back(vertex);
  }
  vertexCountLOD.emplace_back(verticesLowLOD.size());
  vertexCountLOD.emplace_back(verticesHighLOD.size());

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  {
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glimac::ShapeVertex), _vertices.data(), GL_STATIC_DRAW);
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

/**
 * @param cameraPos : Camera position, for LOD computing.
 */
template<is_positionable Element>
void ElementManager<Element>::draw(const glm::vec3& cameraPos, const glm::mat4& viewMatrix) const {
  static glm::mat4 projMatrix = glm::perspective(
    glm::radians(70.f), Config::get().ASPECT_RATIO, 0.1f, 100.f
  );

  glBindVertexArray(_vao);
  {
    _shader->use();

    // glUniforms
    _shader->setUniformTexture();

    // glBindTexture
    _shader->enableActiveTextures();

    // Matrix shit
    for (auto& element : elements) {
      float d      = glm::distance(cameraPos, element->getPosition());
      int   offset = 0;

      glm::mat4 modelMatrix  = getModelMatrix(*element);
      glm::mat4 MVPMatrix    = projMatrix * viewMatrix * modelMatrix;
      glm::mat4 MVMatrix     = viewMatrix * modelMatrix;
      glm::mat4 NormalMatrix = glm::transpose(glm::inverse(modelMatrix));

      // glUniformMatrix
      _shader->setUniformMatrix(MVPMatrix, MVMatrix, NormalMatrix);

      if (d < Config::get().LOD_HIGH_DISTANCE_THRESHOLD) {
        glDrawArrays(GL_TRIANGLES, vertexCountLOD.at(0), static_cast<GLsizei>(_vertices.size() - vertexCountLOD.at(0)));
      }
      else {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCountLOD.at(0)));
      }

      // glDrawArrays
    }

    _shader->disableActiveTextures();
  }
  glBindVertexArray(0);
}

#endif
