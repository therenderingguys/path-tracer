// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef __MODEL_H__
#define __MODEL_H__

#include <glm/glm.hpp>
#include <sstream>
#include <vector>

class Model {
private:
  std::vector<glm::vec3> mVerts;
  std::vector<std::vector<int>> mFaces;
  static void doubleSlashFaceFormat(std::istringstream &iss,
                                    std::vector<int> &f);
  static void singlSlashFaceFormat(std::istringstream &iss,
                                   std::vector<int> &f);
  static void spaceDelimitedFormat(std::istringstream &iss,
                                   std::vector<int> &f);

public:
  Model(const char *filename);
  ~Model();
  int nverts();
  int nfaces();
  glm::vec3 vert(int i);
  std::vector<int> face(int idx);
};

#endif //__MODEL_H__
