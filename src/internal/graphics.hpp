#ifndef __GRAPHICS_FOR_FISH__
#define __GRAPHICS_FOR_FISH__

#include <array>
#include <p6/p6.h>

namespace Graphics {
using Color = std::array<float, 4>;
using DrawFunction = std::function<void()>;

namespace NamedColor {
static const Color BLACK = {0, 0, 0, 1};
static const Color RED = {1, 0, 0, 1};
static const Color GREEN = {0, 1, 0, 1};
static const Color BLUE = {0, 0, 1, 1};
static const Color WHITE = {1, 1, 1, 1};
static const Color NONE = {0, 0, 0, 0};
}; // namespace NamedColor

/**
 * Translates a `Color` (`std::array<float, 4>`) to a `p6::Color`.
 */
inline static p6::Color top6(const Color &color) {
  return {color[0], color[1], color[2], color[3]};
}

inline void draw(p6::Context &ctx, const DrawFunction &drawFunction,
                 const Color &stroke = {0, 0, 0, 0},
                 const Color &fill = {0, 0, 0, 0}) {
  float baseStrokeWeight = ctx.stroke_weight;
  ctx.use_stroke = stroke[3] > 0;
  ctx.stroke = top6(stroke);
  ctx.use_fill = fill[3] > 0;
  ctx.fill = top6(fill);
  ctx.stroke_weight = baseStrokeWeight / 10.f;
  drawFunction();
  ctx.stroke_weight = baseStrokeWeight;
}

}; // namespace Graphics

#endif
