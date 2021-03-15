// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window/glfwWindow.h"
#include "window/pixelBuffer.h"
#include <catch2/catch.hpp>

TEST_CASE("Window PixelBuffer Test", "[pixelBuffer][window]") {
  GWindowMgr gWindow("Test");
  glm::u8vec3 blue(0, 0, 255);
  for (size_t y = 0; y < gWindow.Height(); y++) {
    for (size_t x = 0; x < gWindow.Height(); x++) {
      gWindow.setPixel(x, y, blue);
    }
  }
  auto pixelBuffer = std::move(gWindow.getPixelBuffer());
  for (size_t y = 0; y < gWindow.Height(); y++) {
    for (size_t x = 0; x < gWindow.Height(); x++) {
      REQUIRE(blue == pixelBuffer->getPixel<glm::u8vec3>(x, y));
    }
  }
}