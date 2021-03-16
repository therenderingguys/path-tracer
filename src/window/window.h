/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "pixelBuffer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

typedef std::function<void()> drawCallBack;

class Window {
protected:
  std::string title;
  std::unique_ptr<PixelBuffer> mPixelBuffer;
  std::vector<drawCallBack> drawFunctors;
  void draw();

public:
  Window(std::string title, std::unique_ptr<PixelBuffer> pixelBuffer);
  Window(std::string title, size_t width, size_t height);
  virtual void init() = 0;
  virtual void run() = 0;
  size_t width() const { return mPixelBuffer->width(); }
  size_t height() const { return mPixelBuffer->height(); }
  std::string Title() const { return title; }
  void setPixelBuffer(std::unique_ptr<PixelBuffer> pixelBuffer);
  PixelBuffer *getPixelBuffer();
  void insertDrawCallback(drawCallBack &db);
  const std::vector<drawCallBack> &getDrawCallBacks();
  void setPixel(size_t x, size_t y, uint8_t color);
  void setPixel(size_t x, size_t y, glm::u8vec4 color);
  void setPixel(size_t x, size_t y, glm::u8vec3 color);
};

#endif // __WINDOW_H__