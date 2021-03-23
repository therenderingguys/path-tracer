/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include "shape.h"

#include "texture.h"
#include "window/pixelBuffer.h"
#include <memory>
#include <string>

class Rectangle : public Shape {
public:
  Rectangle(const glm::vec3 &p1, float width, float height);
  void render(int positionHandle, int modelHandle, int textureHandle);
  void render(int positionHandle, int modelHandle, int colorHandle,
              float *color);
  virtual ~Rectangle(void);
  void setTexture(std::unique_ptr<Texture> texture);
  void setPixelBuffer(std::unique_ptr<PixelBuffer> pb);

private:
  void storePoints(const glm::vec3 &p1, const glm::vec3 &p2,
                   const glm::vec3 &p3, const glm::vec3 &p4);
  void initialize(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3,
                  const glm::vec3 &p4);
  std::unique_ptr<Texture> mTexture;
  std::unique_ptr<PixelBuffer> mPixelBuffer;
};

#endif //__RECTANGLE_H__
