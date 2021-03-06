// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "renderer/pixelBuffer.h"
#include "window/glfwWindow.h"
#include <catch2/catch.hpp>

TEST_CASE("Window PixelBuffer Test", "[pixelBuffer][window]") {
  // TODO re-enable this test case
  // https://github.com/therenderingguys/path-tracer/issues/34
  // GLWindow gWindow("Test");
  // glm::u8vec3 blue(0, 0, 255);
  // for (size_t y = 0; y < gWindow.height(); y++) {
  //  for (size_t x = 0; x < gWindow.width(); x++) {
  //    gWindow.setPixel(x, y, blue);
  //  }
  //}
  // PixelBuffer *pixelBuffer = gWindow.getPixelBuffer();
  // for (size_t y = 0; y < gWindow.height(); y++) {
  //  for (size_t x = 0; x < gWindow.width(); x++) {
  //    REQUIRE(blue == pixelBuffer->getPixel<glm::u8vec3>(x, y));
  //  }
  //}
}