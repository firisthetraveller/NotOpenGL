#pragma once
#include <vector>
#include "common.hpp"

namespace glimac {

// Représente un cône ouvert discrétisé dont la base est centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
std::vector<ShapeVertex> cube_vertices(float height = 1.f);

} // namespace glimac
