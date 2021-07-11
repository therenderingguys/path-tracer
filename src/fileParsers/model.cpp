// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "model.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void Model::singlSlashFaceFormat(std::istringstream &iss,
                                 std::vector<glm::vec3> &f) {
  if (iss.str().find("/") == std::string::npos) {
    return;
  }
  char trash;
  glm::vec3 tmp;
  while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
    for (int i = 0; i < 3; i++) {
      tmp[i]--;
    } // in wavefront obj all indices start at 1, not zero
    f.push_back(tmp);
  }
}
void Model::doubleSlashFaceFormat(std::istringstream &iss,
                                  std::vector<glm::vec3> &f) {
  if (iss.str().find("//") == std::string::npos) {
    return;
  }
  char trash;
  glm::vec3 tmp;
  while (iss >> tmp[0] >> trash >> trash >> tmp[1]) {
    for (int i = 0; i < 2; i++) {
      tmp[i]--;
    } // in wavefront obj all indices start at 1, not zero
    f.push_back(tmp);
  }
}
void Model::spaceDelimitedFormat(std::istringstream &iss,
                                 std::vector<glm::vec3> &f) {
  glm::vec3 tmp;
  while (iss >> tmp[0]) {
    tmp[0]--; // in wavefront obj all indices start at 1, not zero
    f.push_back(tmp);
  }
}

Model::Model(const char *objFilename)
    : mVerts(), mFaces(), mNorms(), mUVTextureCoord() {
  loadOBJ(objFilename);
}

Model::Model(const char *objFilename, const char *textureFileName)
    : mVerts(), mFaces(), mNorms(), mUVTextureCoord() {
  loadOBJ(objFilename);
  loadTexture(textureFileName);
}
void Model::loadTexture(const char *filename) {
  mTexture = ImageImport::importAsPPM(filename);
}
void Model::loadOBJ(const char *filename) {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail())
    return;
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      glm::vec3 v;
      for (int i = 0; i < 3; i++)
        iss >> v[i];
      mVerts.push_back(v);
    } else if (!line.compare(0, 3, "vn ")) {
      iss >> trash >> trash;
      glm::vec3 n;
      for (int i = 0; i < 3; i++) {
        iss >> n[i];
      }
      mNorms.push_back(n);
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      glm::vec2 uv;
      for (int i = 0; i < 2; i++) {
        iss >> uv[i];
      }
      mUVTextureCoord.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<glm::vec3> f;
      iss >> trash;
      doubleSlashFaceFormat(iss, f);
      singlSlashFaceFormat(iss, f);
      spaceDelimitedFormat(iss, f);
      mFaces.push_back(f);
    }
  }
}

Model::~Model() {}

size_t Model::nverts() { return mVerts.size(); }

size_t Model::nfaces() { return mFaces.size(); }

std::vector<int> Model::face(size_t idx) {
  std::vector<int> face;
  for (size_t i = 0; i < mFaces[idx].size(); i++) {
    face.push_back(mFaces[idx][i][static_cast<size_t>(FaceIndex::vertex)]);
  }
  return face;
}

glm::vec3 Model::vert(size_t i) { return mVerts[i]; }

glm::vec2 Model::uv(int iface, int nvert) {
  assert(mTexture != nullptr);
  int idx = mFaces[iface][nvert][static_cast<size_t>(FaceIndex::uv)];
  return glm::vec2({mUVTextureCoord[idx].x * mTexture->width(),
                    mUVTextureCoord[idx].y * mTexture->height()});
}
