// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "pixelBuffer.h"
#include <iostream>

PixelBuffer::PixelBuffer(size_t width, size_t height, ColorChannels cc)
    : mSize{width, height}, mChannel(cc), mBuffer() {
  mBuffer.resize(mSize.Height * mSize.Width * getColorChannels());
  std::fill(mBuffer.begin(), mBuffer.end(), 0);
}

const std::vector<uint8_t> &PixelBuffer::buffer() const { return mBuffer; }

uint8_t *PixelBuffer::data() { return mBuffer.data(); }

void PixelBuffer::resizeBuffer(size_t width, size_t height) {
  this->mSize.Width = width;
  this->mSize.Height = height;
  mBuffer.resize(width * height * getColorChannels());
}

void PixelBuffer::setPixel(size_t x, size_t y, uint8_t color) {
  assert(mChannel == ColorChannels::BW);
  size_t index = (y * width() + x);
  mBuffer[index] = color;
}

void PixelBuffer::setPixel(size_t x, size_t y, glm::u8vec3 color) {
  assert(mChannel == ColorChannels::RGB);
  size_t index = (y * width() + x) * getColorChannels();
  // std::cout << "index: " << index << std::endl;
  mBuffer[index] = color[0];
  mBuffer[index + 1] = color[1];
  mBuffer[index + 2] = color[2];
}

void PixelBuffer::setPixel(size_t x, size_t y, glm::u8vec4 color) {
  assert(mChannel == ColorChannels::RGBA);
  size_t index = (y * width() + x) * getColorChannels();
  mBuffer[index] = color[0];
  mBuffer[index + 1] = color[1];
  mBuffer[index + 2] = color[2];
  mBuffer[index + 3] = color[3];
}

void PixelBuffer::setPixel(size_t index, uint8_t color) {
  assert(mChannel == ColorChannels::BW);
  mBuffer[index] = color;
}

void PixelBuffer::setPixel(size_t index, glm::u8vec3 color) {
  assert(mChannel == ColorChannels::RGB);
  mBuffer[index] = color[0];
  mBuffer[index + 1] = color[1];
  mBuffer[index + 2] = color[2];
}

void PixelBuffer::setPixel(size_t index, glm::u8vec4 color) {
  assert(mChannel == ColorChannels::RGBA);
  mBuffer[index] = color[0];
  mBuffer[index + 1] = color[1];
  mBuffer[index + 2] = color[2];
  mBuffer[index + 3] = color[3];
}

template <typename T> T PixelBuffer::getPixel(size_t x, size_t y) {
  throw std::runtime_error("not a supported type");
}

template <> uint8_t PixelBuffer::getPixel<uint8_t>(size_t x, size_t y) {
  assert(mChannel == ColorChannels::BW);
  size_t index = (y * width() + x);
  return mBuffer[index];
}

template <> glm::u8vec3 PixelBuffer::getPixel<glm::u8vec3>(size_t x, size_t y) {
  assert(mChannel == ColorChannels::RGB);
  size_t index = (y * width() + x) * getColorChannels();
  return glm::u8vec3(mBuffer[index], mBuffer[index + 1], mBuffer[index + 2]);
}

template <> glm::u8vec4 PixelBuffer::getPixel<glm::u8vec4>(size_t x, size_t y) {
  assert(mChannel == ColorChannels::RGBA);
  size_t index = (y * width() + x) * getColorChannels();
  return glm::u8vec4(mBuffer[index], mBuffer[index + 1], mBuffer[index + 2],
                     mBuffer[index + 3]);
}

uint8_t &PixelBuffer::operator[](size_t index) {
  if (index >= mBuffer.size()) {
    std::cerr << "PixelBuffer index out of bound, exiting";
    exit(0);
  }
  return mBuffer[index];
}

const uint8_t &PixelBuffer::operator[](size_t index) const {
  if (index >= mBuffer.size()) {
    std::cerr << "PixelBuffer index out of bound, exiting";
    exit(0);
  }
  return mBuffer[index];
}