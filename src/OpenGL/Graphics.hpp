#ifndef __GRAPHICS_OPENGL__
#define __GRAPHICS_OPENGL__

#include "OpenGL/ShaderManager.hpp"
#include <vector>

class Graphics {
  std::vector<ShaderManager> shaders;

public:
  inline void addShader(ShaderManager &shader) { shaders.emplace_back(shader); }
};

#endif
