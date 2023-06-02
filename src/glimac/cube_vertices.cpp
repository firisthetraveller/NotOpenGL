#include "cube_vertices.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace glimac {
std::vector<ShapeVertex> cube_vertices(float height) {
  std::vector<ShapeVertex> vertices;
  float                    position = height / 2;

  // Front face
  vertices.push_back({glm::vec3(-position, -position, position), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, -position, position), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, position, position), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(-position, position, position), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, -position, position), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, position, position), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});

  // Back face
  vertices.push_back({glm::vec3(-position, -position, -position), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, -position, -position), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, position, -position), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)});
  vertices.push_back({glm::vec3(-position, position, -position), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, -position, -position), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, position, -position), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)});

  // Left face
  vertices.push_back({glm::vec3(-position, -position, -position), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, -position, position), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, position, -position), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(-position, position, -position), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(-position, -position, position), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, position, position), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)});

  // Right face
  vertices.push_back({glm::vec3(position, -position, -position), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, -position, position), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, position, -position), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, position, -position), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, -position, position), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, position, position), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)});

  // Top face
  vertices.push_back({glm::vec3(-position, position, -position), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, position, -position), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
  vertices.push_back({glm::vec3(-position, position, position), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, position, position), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, position, -position), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, position, position), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)});

  // Bottom face
  vertices.push_back({glm::vec3(-position, -position, -position), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, -position, -position), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(-position, -position, position), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(-position, -position, position), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)});
  vertices.push_back({glm::vec3(position, -position, -position), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
  vertices.push_back({glm::vec3(position, -position, position), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)});

  return vertices;
}

std::vector<ShapeVertex> reverse_cube_vertices(float height) {
  auto vertices = cube_vertices(height);

  for (auto& vertex : vertices) {
    vertex.normal = -vertex.normal;
  }

  return vertices;
}

}; // namespace glimac
