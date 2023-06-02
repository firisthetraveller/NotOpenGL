#pragma once
#include <vector>
#include "common.hpp"

namespace glimac {

std::vector<ShapeVertex> cube_vertices(float height = 1.f);
std::vector<ShapeVertex> reverse_cube_vertices(float height = 1.f);

} // namespace glimac
