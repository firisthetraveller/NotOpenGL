#pragma once
#include "Shape.hpp"
#include "glm/fwd.hpp"
#include <p6/p6.h>

class Square : public Shape {
private:
  p6::Center _center;
  p6::Radius _radius;
  p6::Rotation _rotation;
  glm::vec2 _movement;

public:
  explicit Square(p6::Center center = {}, p6::Radius radius = {},
                  p6::Rotation rotation = {}, glm::vec2 movement = {});
  ~Square() = default;

  void draw(p6::Context &ctx) override;
  void update() override;

  static Square generate();
};
