/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __PIXEL_BUFFER_H__
#define __PIXEL_BUFFER_H__

#include <glm/glm.hpp>
#include <iostream>
#include <iterator>
#include <vector>

struct Size {
  size_t Width;
  size_t Height;
};

enum class ColorChannels : uint8_t {
  BW = 1,
  RGB = 3,
  RGBA = 4,
};

enum class DataDepth : uint8_t {
  PB_64F,
  PB_32F,
  PB_32U,
  PB_32S,
  PB_16U,
  PB_16S,
  PB_8U,
  PB_8S,
};

class PixelBuffer {
private:
  Size mSize;
  std::vector<uint8_t> mBuffer;
  ColorChannels mChannel;

public:
  PixelBuffer(size_t width, size_t height,
              ColorChannels cc = ColorChannels::RGB);
  void resizeBuffer(size_t width, size_t height);
  void setPixel(size_t x, size_t y, uint8_t color);
  void setPixel(size_t x, size_t y, glm::u8vec3 color);
  void setPixel(size_t x, size_t y, glm::u8vec4 color);

  template <typename T> T getPixel(size_t x, size_t y);

  size_t height() const { return mSize.Height; }
  size_t width() const { return mSize.Width; }
  size_t size() const { return mBuffer.size(); }
  DataDepth depth() const { return DataDepth::PB_8U; }
  inline ColorChannels channels() const { return mChannel; }
  inline uint8_t getColorChannels() const {
    return static_cast<uint8_t>(mChannel);
  }
  const std::vector<uint8_t> &buffer() const;
  uint8_t *data();
  uint8_t &operator[](size_t);
  const uint8_t &operator[](size_t) const;
};

// Note: there are two b\c uint8_t needs to be casted up to not be interpreted
// as a char
inline std::ostream &operator<<(std::ostream &out,
                                const std::vector<uint8_t> &v) {
  if (!v.empty()) {
    out << '[';
    std::copy(v.begin(), v.end(), std::ostream_iterator<uint16_t>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  if (!v.empty()) {
    out << '[';
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const PixelBuffer &pb) {
  out << pb.buffer() << std::endl;
  return out;
}

#endif // __PIXEL_BUFFER_H__