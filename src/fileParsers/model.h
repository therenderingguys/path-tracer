// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef __MODEL_H__
#define __MODEL_H__

#include "renderer/pixelBuffer.h"
#include <glm/glm.hpp>
#include <sstream>
#include <vector>

class Model {
private:
  std::vector<glm::vec3> mVerts;
  std::vector<std::vector<glm::vec3>> mFaces; // vertex/uv/normal
  std::vector<glm::vec3> mNorms;
  std::vector<glm::vec2> mUVTextureCoord;
  static void doubleSlashFaceFormat(std::istringstream &iss,
                                    std::vector<glm::vec3> &f);
  static void singlSlashFaceFormat(std::istringstream &iss,
                                   std::vector<glm::vec3> &f);
  static void spaceDelimitedFormat(std::istringstream &iss,
                                   std::vector<glm::vec3> &f);
  enum class FaceIndex : uint8_t { vertex = 0, uv = 1, normal = 2 };
  void loadOBJ(const char *filename);
  void loadTexture(const char *filename);

public:
  Model(const char *objFilename);
  Model(const char *objFilename, const char *textureFileName);
  ~Model();
  size_t nverts();
  size_t nfaces();
  glm::vec3 vert(size_t i);
  std::vector<int> face(size_t idx);
  glm::vec2 uv(int iface, int nvert);
  std::unique_ptr<PixelBuffer> mTexture;
};

#endif //__MODEL_H__
