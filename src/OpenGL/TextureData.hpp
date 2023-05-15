#ifndef __TEXTURE_DATA__
#define __TEXTURE_DATA__

#include <p6/p6.h>
#include <utility>

/**
 * @param first : Uniform texture location
 * @param second : Texture itself
 */
using TextureData = std::pair<GLint, GLuint>;

#endif
