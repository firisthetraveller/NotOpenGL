#include "TextureManager.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include "img/src/Image.h"

TextureManager::~TextureManager() {
  for (const auto& [path, location] : textureLocations) {
    unloadTexture(path);
  }
}

GLuint TextureManager::loadTexture(const std::string& path) {
  GLuint     tmp{};
  img::Image map = p6::load_image_buffer(path);

  glGenTextures(1, &tmp);
  glBindTexture(GL_TEXTURE_2D, tmp); // Binding de la texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(map.width()), static_cast<int>(map.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, map.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  textureLocations.emplace(path, tmp);

  if (static_cast<int>(tmp) == -1) {
    std::cerr << "Loading texture error on:" << path << "\n";
  }
  return tmp;
}

void TextureManager::unloadTexture(const std::string& path) {
  glDeleteTextures(1, &(textureLocations.at(path)));
}

GLuint TextureManager::getTextureLocation(std::string& path) const {
  return textureLocations.at(path);
}
