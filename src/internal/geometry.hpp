#ifndef __NOT_GEOMETRY__
#define __NOT_GEOMETRY__

#include "glm/fwd.hpp"
#include "glm/geometric.hpp"

namespace Geometry {
/**
 * Returns the distance between two points.
 * @param v1 - First point
 * @param v2 - Second point
 * @return The distance between the two points.
 */
inline float distance2D(glm::vec3 v1, glm::vec3 v2) {
  return glm::distance(glm::vec2(v1), glm::vec2(v2));
}
} // namespace Geometry

#endif
