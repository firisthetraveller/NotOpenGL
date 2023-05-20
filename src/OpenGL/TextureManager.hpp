#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include <map>
#include <p6/p6.h>
#include <string>

#include "TextureData.hpp"

class TextureManager {
private:
  std::map<std::string, GLuint> textureLocations;
  TextureManager() = default;

public:
  TextureManager(TextureManager &copy) = delete;
  TextureManager(TextureManager &&move) = delete;
  ~TextureManager();
  GLuint loadTexture(const std::string &path);
  void unloadTexture(const std::string &path);

  GLuint getTextureLocation(std::string &path) const;

  static TextureManager &getInstance() {
    static TextureManager INSTANCE;

    return INSTANCE;
  };
};

#endif
