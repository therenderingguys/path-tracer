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

const unsigned int Rectangle::indicesCount =
    sizeof(Rectangle::indices) / sizeof(int);

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

  Rectangle::initialize(
      Rectangle::toCartesian(p1.x + width, p1.y + height, width, height),
      Rectangle::toCartesian(p1.x + width, p1.y, width, height),
      Rectangle::toCartesian(p1.x, p1.y, width, height),
      Rectangle::toCartesian(p1.x, p1.y + height, width, height));
}

void Rectangle::initialize(const glm::vec3 &p1, const glm::vec3 &p2,
                           const glm::vec3 &p3, const glm::vec3 &p4) {
  this->stride =
      (Rectangle::textureCoord + Rectangle::dimentions) * sizeof(float);
  this->vertsToDraw = Rectangle::verticies;
  this->vertexAttributes = new float[vertexSize];
  storePoints(p1, p2, p3, p4);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertexAttributes,
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Rectangle::indices), indices,
               GL_STATIC_DRAW);
}

glm::vec3 Rectangle::toCartesian(int i, int j, int width, int height) {
  return glm::vec3(2.0f * (i / static_cast<float>(width)) - 1,
                   -2.0f * (j / static_cast<float>(height)) + 1, 0);
}

void Rectangle::storePoints(const glm::vec3 &p1, const glm::vec3 &p2,
                            const glm::vec3 &p3, const glm::vec3 &p4) {
  int index = 0;
  // Bottom Right
  vertexAttributes[index++] = p1.x;
  vertexAttributes[index++] = p1.y;
  vertexAttributes[index++] = p1.z;

  vertexAttributes[index++] = 1;
  vertexAttributes[index++] = 1;

  // Top Right
  vertexAttributes[index++] = p2.x;
  vertexAttributes[index++] = p2.y;
  vertexAttributes[index++] = p2.z;

  vertexAttributes[index++] = 1;
  vertexAttributes[index++] = 0;

  // Top Left
  vertexAttributes[index++] = p3.x;
  vertexAttributes[index++] = p3.y;
  vertexAttributes[index++] = p3.z;

  vertexAttributes[index++] = 0;
  vertexAttributes[index++] = 0;

  // Bottom Left
  vertexAttributes[index++] = p4.x;
  vertexAttributes[index++] = p4.y;
  vertexAttributes[index++] = p4.z;

  vertexAttributes[index++] = 0;
  vertexAttributes[index++] = 1;
}

Rectangle::~Rectangle(void) {}

void Rectangle::render(int positionHandle, int textureHandle) {
  // Bind texture
  // glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mTexture->genTexture(*mPixelBuffer.get()));
  glVertexAttribPointer(positionHandle, Rectangle::dimentions, GL_FLOAT,
                        GL_FALSE, stride, static_cast<void *>(0));
  glEnableVertexAttribArray(positionHandle);
  glVertexAttribPointer(textureHandle, Rectangle::textureCoord, GL_FLOAT,
                        GL_FALSE, stride,
                        (void *)(Rectangle::dimentions * sizeof(float)));
  glEnableVertexAttribArray(textureHandle);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, Rectangle::indicesCount, GL_UNSIGNED_INT, 0);
}

void Rectangle::setTexture(std::unique_ptr<Texture> texture) {
  this->mTexture = std::move(texture);
}

void Rectangle::setPixelBuffer(std::unique_ptr<PixelBuffer> pb) {
  this->mPixelBuffer = std::move(pb);
}

PixelBuffer *Rectangle::getPixelBuffer() { return mPixelBuffer.get(); }

Texture *Rectangle::getTexture() { return mTexture.get(); }

void Rectangle::setPixel(size_t x, size_t y, uint8_t color) {
  mPixelBuffer->setPixel(x, y, color);
}

void Rectangle::setPixel(size_t x, size_t y, glm::u8vec4 color) {
  mPixelBuffer->setPixel(x, y, color);
}

void Rectangle::setPixel(size_t x, size_t y, glm::u8vec3 color) {
  mPixelBuffer->setPixel(x, y, color);
}