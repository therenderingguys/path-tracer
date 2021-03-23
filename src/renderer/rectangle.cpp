// Copyright (c) 2021 F. Lotfi & Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "rectangle.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Rectangle::Rectangle(const glm::vec3 &p1, float width, float height) : Shape() {
  mPixelBuffer = std::make_unique<PixelBuffer>(width, height);
  Rectangle::initialize(p1, glm::vec3(p1.x + width, p1.y, 0),
                        glm::vec3(p1.x + width, p1.y - height, 0),
                        glm::vec3(p1.x, p1.y - height, 0));
}

void Rectangle::initialize(const glm::vec3 &p1, const glm::vec3 &p2,
                           const glm::vec3 &p3, const glm::vec3 &p4) {
  this->stride = 5 * sizeof(float);
  this->vertsToDraw = 4;
  this->vertexAttributes = new float[4 * 5];
  storePoints(p1, p2, p3, p4);
}

void Rectangle::storePoints(const glm::vec3 &p1, const glm::vec3 &p2,
                            const glm::vec3 &p3, const glm::vec3 &p4) {
  int index = 0;
  // Top Left
  vertexAttributes[index++] = p1.x;
  vertexAttributes[index++] = p1.y;
  vertexAttributes[index++] = p1.z;

  vertexAttributes[index++] = 0; // TODO Fix
  vertexAttributes[index++] = 1;

  // Top Right
  vertexAttributes[index++] = p2.x;
  vertexAttributes[index++] = p2.y;
  vertexAttributes[index++] = p2.z;

  vertexAttributes[index++] = 1; // TODO Fix
  vertexAttributes[index++] = 1;

  // Bottom Right
  vertexAttributes[index++] = p3.x;
  vertexAttributes[index++] = p3.y;
  vertexAttributes[index++] = p3.z;

  vertexAttributes[index++] = 1; // TODO Fix
  vertexAttributes[index++] = 0;

  // Bottom Left
  vertexAttributes[index++] = p4.x;
  vertexAttributes[index++] = p4.y;
  vertexAttributes[index++] = p4.z;

  vertexAttributes[index++] = 0; // TODO Fix
  vertexAttributes[index++] = 0;
}

Rectangle::~Rectangle(void) { delete vertexAttributes; }

void Rectangle::render(int positionHandle, int modelHandle, int textureHandle) {
  // Bind texture
  glBindTexture(GL_TEXTURE_2D, mTexture->genTexture(*mPixelBuffer.get()));
  glEnableVertexAttribArray(positionHandle);
  glEnableVertexAttribArray(textureHandle);
  glDisableVertexAttribArray(modelHandle);
  glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, stride,
                        vertexAttributes);
  glVertexAttribPointer(textureHandle, 2, GL_FLOAT, GL_FALSE, stride,
                        vertexAttributes + 3);
  glDrawArrays(GL_QUADS, 0, vertsToDraw);
}

void Rectangle::render(int positionHandle, int modelHandle, int colorHandle,
                       float *color) {

  glEnableVertexAttribArray(positionHandle);
  glUniform4fv(colorHandle, 1, color);
  glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, stride,
                        vertexAttributes);
  glDrawArrays(GL_QUADS, 0, vertsToDraw);
}

void Rectangle::setTexture(std::unique_ptr<Texture> texture) {
  this->mTexture = std::move(texture);
}

void Rectangle::setPixelBuffer(std::unique_ptr<PixelBuffer> pb) {
  this->mPixelBuffer = std::move(pb);
}