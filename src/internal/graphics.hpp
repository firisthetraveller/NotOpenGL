#pragma once

#include <array>
#include <p6/p6.h>

namespace Graphics {
using Color = std::array<float, 4>;
using DrawFunction = std::function<void()>;

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
