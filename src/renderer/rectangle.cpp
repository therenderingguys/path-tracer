// Copyright (c) 2021 F. Lotfi & Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "rectangle.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int Rectangle::indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

Rectangle::Rectangle(float width, float height) : Shape() {
  glm::vec3 p1(0, 0, 0);
  pbInit(p1, width, height);
}

Rectangle::Rectangle(const glm::vec3 &p1, float width, float height) : Shape() {
  pbInit(p1, width, height);
}

void Rectangle::pbInit(const glm::vec3 &p1, float width, float height) {
  mPixelBuffer = std::make_unique<PixelBuffer>(width, height);
  mTexture = std::make_unique<Texture>();
  Rectangle::initialize(p1, glm::vec3(p1.x + width, p1.y, 0),
                        glm::vec3(p1.x + width, p1.y - height, 0),
                        glm::vec3(p1.x, p1.y - height, 0));
}

void Rectangle::initialize(const glm::vec3 &p1, const glm::vec3 &p2,
                           const glm::vec3 &p3, const glm::vec3 &p4) {
  this->stride = 5 * sizeof(float);
  this->vertsToDraw = 4;
  this->vertexAttributes = new float[vertexSize];
  storePoints(p1, p2, p3, p4);
  glBufferData(GL_ARRAY_BUFFER, vertexSize*sizeof(float), vertexAttributes, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Rectangle::indices), indices, GL_STATIC_DRAW);


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

Rectangle::~Rectangle(void) {}

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

PixelBuffer *Rectangle::getPixelBuffer() { return mPixelBuffer.get(); }

void Rectangle::setPixel(size_t x, size_t y, uint8_t color) {
  mPixelBuffer->setPixel(x, y, color);
}

void Rectangle::setPixel(size_t x, size_t y, glm::u8vec4 color) {
  mPixelBuffer->setPixel(x, y, color);
}

void Rectangle::setPixel(size_t x, size_t y, glm::u8vec3 color) {
  mPixelBuffer->setPixel(x, y, color);
}