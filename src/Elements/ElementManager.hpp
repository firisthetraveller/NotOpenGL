#ifndef __ELEMENTMANAGER__
#define __ELEMENTMANAGER__

#include <p6/p6.h>
#include <vector>

template <typename Element> class ElementManager {
private:
  GLuint _vao{};

public:
  std::vector<std::shared_ptr<Element>> elements;

  ElementManager();
  void draw() const;
  auto getElements() const { return elements; };
  auto begin() { return elements.begin(); };
  auto end() { return elements.end(); };
};

template <typename Element> ElementManager<Element>::ElementManager() {
  glGenVertexArrays(1, &_vao);
}

template <typename Element> void ElementManager<Element>::draw() const {
  glBindVertexArray(_vao);
  {}
  glBindVertexArray(0);
}

#endif
