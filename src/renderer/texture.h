/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include "window/pixelBuffer.h"
#include <glad/glad.h>

class Texture {
private:
  GLuint texture;
  GLuint matToTexture(PixelBuffer &buffer, GLenum minFilter, GLenum magFilter,
                      GLenum wrapFilter);

public:
  Texture();
  GLuint genTexture(PixelBuffer &buffer);
  virtual ~Texture() { glDeleteTextures(1, &this->texture); }
};

#endif