// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "window/pixelBuffer.h"
#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("PixelBuffer RGBA Test", "[pixelBuffer]") {
  PixelBuffer pb(100, 100, ColorChannels::RGBA);
  glm::u8vec4 blueAlpha(0, 0, 255, 127);
  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      pb.setPixel(x, y, blueAlpha);
    }
  }

  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      REQUIRE(blueAlpha == pb.getPixel<glm::u8vec4>(x, y));
    }
  }
}

TEST_CASE("PixelBuffer RGB Test", "[pixelBuffer]") {
  PixelBuffer pb(100, 100, ColorChannels::RGB);
  glm::u8vec3 blue(0, 0, 255);
  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      pb.setPixel(x, y, blue);
    }
  }

  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      REQUIRE(blue == pb.getPixel<glm::u8vec3>(x, y));
    }
  }
}

TEST_CASE("PixelBuffer BW Test", "[pixelBuffer]") {
  PixelBuffer pb(100, 100, ColorChannels::BW);
  uint8_t white = 255;
  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      pb.setPixel(x, y, white);
    }
  }

  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      REQUIRE(white == pb.getPixel<uint8_t>(x, y));
    }
  }
}

TEST_CASE("PixelBuffer Resize Test", "[pixelBuffer]") {
  size_t width = 150, height = 100;
  PixelBuffer pb(width, height);
  REQUIRE(pb.height() == height);
  REQUIRE(pb.width() == width);
  size_t rWidth = 100, rHeight = 200;
  pb.resizeBuffer(rWidth, rHeight);
  REQUIRE(pb.height() == rHeight);
  REQUIRE(pb.width() == rWidth);
}

TEST_CASE("PixelBuffer Print Test", "[pixelBuffer]") {
  size_t width = 4, height = 4;
  std::stringstream sAnsOut;
  std::stringstream sSlnOut;
  PixelBuffer pb(width, height, ColorChannels::BW);
  std::vector<uint16_t> vecTest(16);
  for (int i = 0; i < 16; i++) {
    if (i % 2 == 0) {
      vecTest[i] = 255;
    } else {
      vecTest[i] = 0;
    }
  }
  for (size_t y = 0; y < pb.height(); y++) {
    for (size_t x = 0; x < pb.width(); x++) {
      size_t index = (y * pb.width() + x) * pb.getColorChannels();
      if (index % 2 == 0) {
        pb[index] = 255;
      } else {
        pb[index] = 0;
      }
    }
  }
  sAnsOut << pb;
  sSlnOut << vecTest << std::endl;
  REQUIRE(sAnsOut.str() == sSlnOut.str());
}

TEST_CASE("PixelBuffer Indexing Test", "[pixelBuffer]") {
  size_t width = 4, height = 4;
  PixelBuffer pb(width, height, ColorChannels::BW);
  for (int i = 0; i < pb.size(); i++) {
    if (i % 2 == 0) {
      pb[i] = 255;
    } else {
      pb[i] = 0;
    }
    REQUIRE(pb[i] == pb.buffer()[i]);
    REQUIRE(pb[i] == pb.data()[i]);
  }
}