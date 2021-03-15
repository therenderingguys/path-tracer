// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <catch2/catch.hpp>

#include "window/pixelBuffer.h"

TEST_CASE("PixelBuffer RGBA Test", "[pixelBuffer]") {
  PixelBuffer pb(100, 100, ColorChannels::RGBA);
  glm::u8vec4 blueAlpha(0, 0, 255, 127);
  for (size_t y = 0; y < pb.Height(); y++) {
    for (size_t x = 0; x < pb.Height(); x++) {
      pb.setPixel(x, y, blueAlpha);
    }
  }

  for (size_t y = 0; y < pb.Height(); y++) {
    for (size_t x = 0; x < pb.Height(); x++) {
      REQUIRE(blueAlpha == pb.getPixel<glm::u8vec4>(x, y));
    }
  }
}

TEST_CASE("PixelBuffer RGB Test", "[pixelBuffer]") {
  PixelBuffer pb(100, 100, ColorChannels::RGB);
  glm::u8vec3 blue(0, 0, 255);
  for (size_t y = 0; y < pb.Height(); y++) {
    for (size_t x = 0; x < pb.Height(); x++) {
      pb.setPixel(x, y, blue);
    }
  }

  for (size_t y = 0; y < pb.Height(); y++) {
    for (size_t x = 0; x < pb.Height(); x++) {
      REQUIRE(blue == pb.getPixel<glm::u8vec3>(x, y));
    }
  }
}

TEST_CASE("PixelBuffer BW Test", "[pixelBuffer]") {
  PixelBuffer pb(100, 100, ColorChannels::BW);
  uint8_t white = 255;
  for (size_t y = 0; y < pb.Height(); y++) {
    for (size_t x = 0; x < pb.Height(); x++) {
      pb.setPixel(x, y, white);
    }
  }

  for (size_t y = 0; y < pb.Height(); y++) {
    for (size_t x = 0; x < pb.Height(); x++) {
      REQUIRE(white == pb.getPixel<uint8_t>(x, y));
    }
  }
}