// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "pixelBuffer.h"
#include <iostream>

PixelBuffer::PixelBuffer(size_t width, size_t height, ColorChannels cc)
    : size{width, height}, mChannel(cc), mBuffer() {
  mBuffer.resize(size.Height * size.Width * static_cast<uint8_t>(mChannel));
  std::fill(mBuffer.begin(), mBuffer.end(), 0);
}

const std::vector<uint8_t> &PixelBuffer::buffer() const { return mBuffer; }

uint8_t *PixelBuffer::data() { return mBuffer.data(); }

void PixelBuffer::resizeBuffer(size_t width, size_t height) {
  this->size.Height = height;
  this->size.Width = width;
  mBuffer.resize(width * height * static_cast<uint8_t>(mChannel));
}

void PixelBuffer::setPixel(size_t x, size_t y, uint8_t color) {
  assert(mChannel == ColorChannels::BW);
  size_t index = (y * Width() + x);
  mBuffer[index] = color;
}

void PixelBuffer::setPixel(size_t x, size_t y, glm::u8vec3 color) {
  assert(mChannel == ColorChannels::RGB);
  size_t index = (y * Width() + x) * static_cast<uint8_t>(mChannel);
  std::cout << "index: " << index << std::endl;
  mBuffer[index] = color[0];
  mBuffer[index + 1] = color[1];
  mBuffer[index + 2] = color[2];
}

void PixelBuffer::setPixel(size_t x, size_t y, glm::u8vec4 color) {
  assert(mChannel == ColorChannels::RGBA);
  size_t index = (y * Width() + x) * static_cast<uint8_t>(mChannel);
  mBuffer[index] = color[0];
  mBuffer[index + 1] = color[1];
  mBuffer[index + 2] = color[2];
  mBuffer[index + 3] = color[3];
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