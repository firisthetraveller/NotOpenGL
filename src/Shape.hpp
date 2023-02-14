#pragma once
#include <p6/p6.h>

class Shape {
public:
  Shape() = default;
  // Shape(const Shape &other);
  virtual ~Shape() = default;
  virtual void draw(p6::Context &ctx) = 0;
  virtual void update() = 0;
};
