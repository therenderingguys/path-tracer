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

class PixelBuffer {
private:
  Size size;
  std::vector<uint8_t> mBuffer;
  ColorChannels mChannel;

public:
  PixelBuffer(size_t width, size_t height,
              ColorChannels cc = ColorChannels::RGB);
  void resizeBuffer(size_t h, size_t w);
  void setPixel(size_t x, size_t y, uint8_t color);
  void setPixel(size_t x, size_t y, glm::u8vec3 color);
  void setPixel(size_t x, size_t y, glm::u8vec4 color);

  template <typename T> T getPixel(size_t x, size_t y);

  size_t Height() const { return size.Height; }
  size_t Width() const { return size.Width; }
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