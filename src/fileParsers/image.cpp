// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "image.h"
#include <fstream>
#include <glm/glm.hpp>

void ImageExport::exportAsPPM(std::string fileName, PixelBuffer *pb) {
  std::ofstream ofs(fileName, std::ios_base::out | std::ios_base::binary);
  ofs << "P3\n" << pb->width() << ' ' << pb->height() << "\n255\n";
  for (size_t y = 0; y < pb->height(); y++) {
    for (size_t x = 0; x < pb->width(); x++) {
      glm::u8vec3 pixel = pb->getPixel<glm::u8vec3>(x, y);
      ofs << static_cast<short>(pixel.r) << " " << static_cast<short>(pixel.g)
          << " " << static_cast<short>(pixel.b) << std::endl;
    }
  }
  ofs.close();
}

void eatComment(std::ifstream &f) {
  char linebuf[1024];
  char ppp;
  while (ppp = f.peek(), ppp == '\n' || ppp == '\r')
    f.get();
  if (ppp == '#')
    f.getline(linebuf, 1023);
}

std::unique_ptr<PixelBuffer> ImageImport::importAsPPM(std::string fileName) {
  std::unique_ptr<PixelBuffer> returnBuffer = nullptr;

  std::ifstream f(fileName.c_str(), std::ios_base::binary);
  if (f.fail()) {
    std::cout << "Could not open file: " << fileName << std::endl;
    return returnBuffer;
  }
  int width = 0, height = 0;
  // get type of file
  eatComment(f);
  int mode = 0;
  std::string s;
  f >> s;
  if (s == "P3")
    mode = 3;
  else if (s == "P6")
    mode = 6;

  // get w
  eatComment(f);
  f >> width;

  // get h
  eatComment(f);
  f >> height;

  // get bits
  eatComment(f);
  int bits = 0;
  f >> bits;

  // error checking
  if (mode != 3 && mode != 6) {
    std::cout << "Unsupported magic number" << std::endl;
    f.close();
    return returnBuffer;
  }
  if (width < 1) {
    std::cout << "Unsupported width: " << width << std::endl;
    f.close();
    return returnBuffer;
  }
  if (height < 1) {
    std::cout << "Unsupported height: " << height << std::endl;
    f.close();
    return returnBuffer;
  }
  if (bits < 1 || bits > 255) {
    std::cout << "Unsupported number of bits: " << bits << std::endl;
    f.close();
    return returnBuffer;
  }

  // load image data
  returnBuffer = std::make_unique<PixelBuffer>(width, height);

  if (mode == 6) {
    f.get();
    f.read(reinterpret_cast<char *>(returnBuffer->data()),
           returnBuffer->size());
  } else if (mode == 3) {
    for (size_t i = 0; i < returnBuffer->height() * returnBuffer->width();
         i++) {
      int v;
      glm::vec3 pixel;
      f >> v;
      pixel.r = v;
      f >> v;
      pixel.g = v;
      f >> v;
      pixel.b = v;
      returnBuffer->setPixel(i, pixel);
    }
  }

  // close file
  f.close();
  return returnBuffer;
}