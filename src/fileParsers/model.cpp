// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void Model::singlSlashFaceFormat(std::istringstream &iss,
                                  std::vector<int> &f) {
  if (iss.str().find("/") == std::string::npos) {
    return;
  }
  int itrash, idx;
  char trash;
  while (iss >> idx >> trash >> itrash >> trash >> itrash) {
    idx--; // in wavefront obj all indices start at 1, not zero
    f.push_back(idx);
  }
}
void Model::doubleSlashFaceFormat(std::istringstream &iss,
                                  std::vector<int> &f) {
  if (iss.str().find("//") == std::string::npos) {
    return;
  }
  int itrash, idx;
  char trash;
  while (iss >> idx >> trash >> trash >> itrash) {
    idx--; // in wavefront obj all indices start at 1, not zero
    f.push_back(idx);
  }
}
void Model::spaceDelimitedFormat(std::istringstream &iss, std::vector<int> &f) {
  int idx;
  while (iss >> idx) {
    idx--; // in wavefront obj all indices start at 1, not zero
    f.push_back(idx);
  }
}

Model::Model(const char *filename) : mVerts(), mFaces() {
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
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<int> f;
      iss >> trash;
      doubleSlashFaceFormat(iss, f);
      singlSlashFaceFormat(iss, f);
      spaceDelimitedFormat(iss, f);
     
      mFaces.push_back(f);
    }
  }
  std::cerr << "# v# " << mVerts.size() << " f# " << mFaces.size() << std::endl;
}

Model::~Model() {}

int Model::nverts() { return (int)mVerts.size(); }

int Model::nfaces() { return (int)mFaces.size(); }

std::vector<int> Model::face(int idx) { return mFaces[idx]; }

glm::vec3 Model::vert(int i) { return mVerts[i]; }
