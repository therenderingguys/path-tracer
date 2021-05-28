/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include "shape.h"

#include "pixelBuffer.h"
#include "texture.h"
#include <memory>
#include <string>

class Rectangle : public Shape {
public:
  static const unsigned int indices[];
  static const unsigned int indicesCount;
  // 4 points in a quad, 2 texture coordinates, 3 for position
  static const unsigned int verticies = 4;
  static const unsigned int dimentions = 3;
  static const unsigned int textureCoord = 2;
  static const unsigned int vertexSize =
      verticies * (dimentions + textureCoord);
  Rectangle(float width, float height);
  Rectangle(const glm::vec3 &p1, float width, float height);
  void render(int positionHandle, int textureHandle);
  virtual ~Rectangle(void);
  void setTexture(std::unique_ptr<Texture> texture);
  void setPixelBuffer(std::shared_ptr<PixelBuffer> pb);
  std::shared_ptr<PixelBuffer> getPixelBuffer();
  Texture *getTexture();
  size_t width() const { return mPixelBuffer->width(); }
  size_t height() const { return mPixelBuffer->height(); }
  void setPixel(size_t x, size_t y, uint8_t color);
  void setPixel(size_t x, size_t y, glm::u8vec4 color);
  void setPixel(size_t x, size_t y, glm::u8vec3 color);
  void storePoints(const glm::vec3 &p1, const glm::vec3 &p2,
                   const glm::vec3 &p3, const glm::vec3 &p4);
  static glm::vec3 toCartesian(int i, int j, int width, int height);

private:
  void pbInit(const glm::vec3 &p1, float width, float height);
  void initialize(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3,
                  const glm::vec3 &p4);
  std::unique_ptr<Texture> mTexture;
  std::shared_ptr<PixelBuffer> mPixelBuffer;
};

#endif //__RECTANGLE_H__
