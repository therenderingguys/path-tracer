/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include "pixelBuffer.h"
#include <glad/glad.h>

class Texture {
private:
  bool mVisited;
  GLuint mTexture;
  GLuint matToTexture(PixelBuffer &buffer, GLenum minFilter, GLenum magFilter,
                      GLenum wrapFilter);

public:
  Texture() : mVisited(false), mTexture(0) {}
  GLuint genTexture(PixelBuffer &buffer);
  inline GLuint getTexture() const { return mTexture; }
  virtual ~Texture() { glDeleteTextures(1, &this->mTexture); }
};

#endif