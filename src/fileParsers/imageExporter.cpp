// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "imageExporter.h"
#include <fstream>

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