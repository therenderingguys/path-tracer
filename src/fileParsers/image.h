// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "renderer/pixelBuffer.h"

class ImageExport {
private:
  ImageExport() = delete;

public:
  static void exportAsPPM(std::string fileName, PixelBuffer *pb);
};

class ImageImport {
private:
  ImageImport() = delete;

public:
  static std::unique_ptr<PixelBuffer> importAsPPM(std::string fileName);
};

#endif //__IMAGE_H__