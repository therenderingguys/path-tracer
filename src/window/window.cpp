// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window.h"

Window::Window(std::string title, size_t width, size_t height) : title(title) {
  mPixelBuffer = std::make_unique<PixelBuffer>(width, height);
}

Window::Window(std::string title, std::unique_ptr<PixelBuffer> pixelBuffer)
    : title(title), mPixelBuffer(std::move(pixelBuffer)) {}

void Window::draw() {
  for (const std::function<void()> &df : drawFunctors) {
    df();
  }
}
void Window::setPixelBuffer(std::unique_ptr<PixelBuffer> pixelBuffer) {
  mPixelBuffer = std::move(pixelBuffer);
}

std::unique_ptr<PixelBuffer> &Window::getPixelBuffer() { return mPixelBuffer; }

void Window::insertDrawCallback(drawCallBack &db) {
  this->drawFunctors.push_back(db);
}

const std::vector<drawCallBack> &Window::getDrawCallBacks() {
  return drawFunctors;
}

void Window::setPixel(size_t x, size_t y, uint8_t color) {
  mPixelBuffer->setPixel(x, y, color);
}

void Window::setPixel(size_t x, size_t y, glm::u8vec4 color) {
  mPixelBuffer->setPixel(x, y, color);
}

void Window::setPixel(size_t x, size_t y, glm::u8vec3 color) {
  mPixelBuffer->setPixel(x, y, color);
}
